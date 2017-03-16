#include "newcardsession.h"
#include "ui_newcardsession.h"
#include "statuswidget.h"

#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QBuffer>
#include <QDateTime>

NewCardSession::NewCardSession(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewCardSession)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    connect(ui->OutputTextEdit, SIGNAL(copyAvailable(bool)), this, SLOT(readyCopyAvailable(bool)));

    isJCOPConnected = false;
    isVCRConnected = false;

    was000102 = false;

    tcpSocketJCop = new QTcpSocket();
    tcpSocketVCR = new QTcpSocket();

    QDateTime dateTime = dateTime.currentDateTime();
    curFile = "Card Session: " + dateTime.toString("yyyy-MM-dd-hh-mm-ss");

    StatusWidget *sw = new StatusWidget(this);
    ui->mainVerticalLayout->addWidget(sw,0, Qt::AlignLeft);
    ui->mainVerticalLayout->setStretch(0,0);
    ui->mainVerticalLayout->setStretch(1,2);
    ui->mainVerticalLayout->setStretch(2,0);

    loadingTimer = new QTimer();
    this->loadingTimer->setInterval(TIMER_INTERVAL);
    connect(loadingTimer, SIGNAL(timeout()), this, SLOT(doAutoCheck()));

    this->loadingTimer->start();
}

void NewCardSession::setAutoChecked(bool set)
{
    ui->autoConnectCheckBox->setChecked(set);
}

void NewCardSession::doAutoCheck()
{
    if (ui->autoConnectCheckBox->isChecked() == false)
        return;

    bool ok = false;

    this->loadingTimer->stop();

    on_autoConnectCheckBox_clicked();

    if (isJCOPConnected == false)
    {
        tcpSocketJCop->connectToHost(QHostAddress::LocalHost, ui->JCopPortLineEdit->text().toInt(&ok, 10));
        if (tcpSocketJCop->waitForConnected(100))
        {
            tcpSocketJCop->close();

            on_connectPushButton_clicked();
        }
    }

    this->loadingTimer->start();
}

bool NewCardSession::save()
{
    //    if (isUntitled) {
    //        return saveAs();
    //    } else {
    //        return saveFile(curFile);
    //    }

    return true;
}

bool NewCardSession::saveAs()
{
    //    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
    //                                                    curFile);
    //    if (fileName.isEmpty())
    //        return false;

    //    return saveFile(fileName);

    return true;
}

NewCardSession::~NewCardSession()
{
    delete ui;
}

void NewCardSession::closeEvent(QCloseEvent *event)
{
    if (cleanUp()) {
        event->accept();
    } else {
        event->ignore();
    }
}

bool NewCardSession::cleanUp()
{
    loadingTimer->stop();
    if (isJCOPConnected)
        tcpSocketJCop->close();

    if (isVCRConnected)
        tcpSocketVCR->close();

#ifdef SHOW_DEBUG
    qDebug() << "Closing and clean up" << endl;
#endif

    return true;
}

////List the available readers
//LONG NewCardSession::doListCardReaders()
//{
//    SCARDCONTEXT    m_hSC = NULL;
//    LPTSTR          pmszReaders = NULL;
//    LONG            lReturn2;
//    DWORD           cch = SCARD_AUTOALLOCATE;
//    QStringList     m_csReaderList;
//    int             m_readerNumber;

//    LONG lReturn = SCARD_S_SUCCESS;

//    // Calling PCSC low level functions
//    lReturn = SCardEstablishContext(SCARD_SCOPE_USER,
//                                    NULL,
//                                    NULL,
//                                    &m_hSC);

//    if ( lReturn != SCARD_S_SUCCESS ) {
//        doWriteOutput("Failed to establish context with SCardEstablishContext\n");

//        return lReturn;
//    }

//    // hSC was set by a previous call to SCardEstablishContext (during object creation).
//    lReturn = SCardListReaders(m_hSC,
//                               NULL,
//                               (LPTSTR)&pmszReaders,
//                               &cch );

//    switch( lReturn )
//    {
//    case SCARD_E_NO_READERS_AVAILABLE:
//        doWriteOutput("No Readers Available \n");
//        break;

//    case SCARD_S_SUCCESS:
//        // Do something with the multi string of readers.
//        // A double-null terminates the list of values.
//        m_csReaderList.clear();

//        // if in case ther reader are more than 1
//        LPTSTR	pReader;
//        pReader = pmszReaders;

//        m_readerNumber = 0;

//        while ( '\0' != *pReader )
//        {
//            QString tmp;
//            tmp.clear();

//            while ('\0' != *pReader)
//            {
//                tmp.append(*pReader);
//                pReader++;
//            }

//            pReader++;  // skip null

//            // save to the list
//            m_csReaderList <<  tmp;
//            m_readerNumber++;
//        }

//        // Free the memory.
//        lReturn2 = SCardFreeMemory(m_hSC,
//                                   pmszReaders );

//        if ( SCARD_S_SUCCESS != lReturn2 )
//            doWriteOutput("Failed to free memory \n");

//        break;

//    default:
//        doWriteOutput("SCardListReaders Failed \n");
//        break;
//    }

//    return lReturn;
//}

QTextEdit *NewCardSession::getOutputWindow()
{
    return (QTextEdit*)ui->OutputTextEdit;
}

void NewCardSession::doWriteOutput(QString text)
{
    ui->OutputTextEdit->append(text);
}

void NewCardSession::on_clearPushButton_clicked()
{
    ui->OutputTextEdit->clear();
}

void NewCardSession::readyCopyAvailable(bool status)
{
    emit copyAvailable(status);
}

void NewCardSession::on_connectPushButton_clicked()
{
    disconnect(tcpSocketJCop, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayErrorJCOP(QAbstractSocket::SocketError)));
    disconnect(tcpSocketVCR, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayErrorVCR(QAbstractSocket::SocketError)));

    disconnect(tcpSocketJCop, SIGNAL(connected()), this, SLOT(doJCOPConnected()));
    disconnect(tcpSocketVCR, SIGNAL(connected()), this, SLOT(doVCRConnected()));

    disconnect(tcpSocketJCop, SIGNAL(disconnected()), this, SLOT(doJCOPDisconnected()));
    disconnect(tcpSocketVCR, SIGNAL(disconnected()), this, SLOT(doVCRDisconnected()));

    disconnect(tcpSocketJCop, SIGNAL(readyRead()), this, SLOT(doJCOPRead()));
    disconnect(tcpSocketVCR, SIGNAL(readyRead()), this, SLOT(doVCRRead()));

    if (ui->connectPushButton->text().compare("Disconnect", Qt::CaseInsensitive) == 0)
    {
        tcpSocketJCop->close();
        tcpSocketVCR->close();

        isJCOPConnected = false;
        isVCRConnected = false;

        ui->connectPushButton->setText("Connect");

        Sleep(500);

        return;
    }

    bool ok = false;

    connect(tcpSocketJCop, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayErrorJCOP(QAbstractSocket::SocketError)));
    connect(tcpSocketVCR, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayErrorVCR(QAbstractSocket::SocketError)));

    connect(tcpSocketJCop, SIGNAL(connected()), this, SLOT(doJCOPConnected()));
    connect(tcpSocketVCR, SIGNAL(connected()), this, SLOT(doVCRConnected()));

    connect(tcpSocketJCop, SIGNAL(disconnected()), this, SLOT(doJCOPDisconnected()));
    connect(tcpSocketVCR, SIGNAL(disconnected()), this, SLOT(doVCRDisconnected()));

    connect(tcpSocketJCop, SIGNAL(readyRead()), this, SLOT(doJCOPRead()));
    connect(tcpSocketVCR, SIGNAL(readyRead()), this, SLOT(doVCRRead()));

    tcpSocketJCop->connectToHost(QHostAddress::LocalHost, ui->JCopPortLineEdit->text().toInt(&ok, 10));
}

void NewCardSession::doVCRRead()
{
    int readLen = 0;
    char buf[1024] = {0x00};
    int len, val = 0;

    QDataStream in(tcpSocketVCR);
    in.setVersion(QDataStream::Qt_5_5);

    if (_blockSizeVCR == 0)
    {
        arrayVCR.clear();

        len = tcpSocketVCR->bytesAvailable();
        val = (int)sizeof(quint16);
        readLen = tcpSocketVCR->read(buf, len );
        arrayVCR.append(buf, readLen);

        if ( len < val)
            return;

        in >> _blockSizeVCR;
#ifdef SHOW_DEBUG
        qDebug() << "_blockSizeVCRnow " << _blockSizeVCR;
#endif
    }

    len = tcpSocketVCR->bytesAvailable();
    readLen = tcpSocketVCR->read(buf, len );
    arrayVCR.append(buf, readLen);
    if (len < _blockSizeVCR)
        return;

    quint8 commandLen;
    in >> commandLen;
#ifdef SHOW_DEBUG
    qDebug() << "Received command " << commandLen;
#endif

    QString msg = arrayVCR.toHex().toUpper();

#ifdef SHOW_DEBUG
    qDebug() << "VCR >> " << msg;
#endif

    if (msg.isEmpty())
        return;

    if (msg.length() <= 4)
    {
        _blockSizeVCR = 1;
        return;
    }

    _blockSizeVCR= 0;

    doWriteOutput("VCR -> PC: " + msg +"\n");

    if (msg == "000104")
    {
        if (was000102)
        {
            //sent reset to JCOP
            QString ResetCommandJcop = "0021000400000000";
            QByteArray array = QByteArray::fromHex(ResetCommandJcop.toLatin1());
            tcpSocketJCop->write(array);

            doWriteOutput("PC -> JCP: "+ array.toHex().toUpper() +"\n");
            was000102 = false;
        }

        if (isVCRConnected && JCOPAtr.isNull() == false && JCOPAtr.isEmpty() == false)
        {
            QString packet = QString("%1").arg(JCOPAtr.length()/2, 4, 16, QChar('0')) + JCOPAtr;
            QByteArray array = QByteArray::fromHex(packet.toLatin1());
            tcpSocketVCR->write(array);

            doWriteOutput("PC -> VCR: "+ array.toHex().toUpper() +"\n");
        }

    }
    else if (msg == "000102")
    {

        was000102 = true;

    }
    else if (msg == "000102000104")
    {
        //sent reset to JCOP
        QString ResetCommandJcop = "0021000400000000";
        QByteArray array = QByteArray::fromHex(ResetCommandJcop.toLatin1());
        tcpSocketJCop->write(array);

        doWriteOutput("PC -> JCP: "+ array.toHex().toUpper() +"\n");
        was000102 = false;

        QString packet = QString("%1").arg(JCOPAtr.length()/2, 4, 16, QChar('0')) + JCOPAtr;
        array = QByteArray::fromHex(packet.toLatin1());
        tcpSocketVCR->write(array);

        doWriteOutput("PC -> VCR: "+ array.toHex().toUpper() +"\n");
    }
    else
    {
        QString ctrl = msg.left(4);
        QString cmd = msg.right(msg.length() - 4);

        QString cmdToJCop = "0100" + ctrl + cmd;
        QByteArray array = QByteArray::fromHex(cmdToJCop.toLatin1());
        tcpSocketJCop->write(array);

        doWriteOutput("PC -> JCP: "+ array.toHex().toUpper() +"\n");

    }

}

void NewCardSession::doJCOPRead()
{
    int readLen = 0;
    char buf[1024] = {0x00};
    int len, val = 0;

    QDataStream in(tcpSocketJCop);
    in.setVersion(QDataStream::Qt_5_5);

    if (_blockSizeJCOP == 0)
    {
        arrayJCOP.clear();

        len = tcpSocketJCop->bytesAvailable();
        val = (int)sizeof(quint16);

        readLen = tcpSocketJCop->read(buf, len );
        arrayJCOP.append(buf, readLen);

        if ( len < val)
            return;

        in >> _blockSizeJCOP;
#ifdef SHOW_DEBUG
        qDebug() << "_blockSizeJCOP " << _blockSizeJCOP;
#endif
    }

    len = tcpSocketJCop->bytesAvailable();
    readLen = tcpSocketJCop->read(buf, len );
    arrayJCOP.append(buf, readLen);
    if (len < _blockSizeJCOP)
        return;

    quint8 commandLen;
    in >> commandLen;
#ifdef SHOW_DEBUG
    qDebug() << "Received command " << commandLen;
#endif


    QString msg = arrayJCOP.toHex().toUpper();

#ifdef SHOW_DEBUG
    qDebug() << "JCOP >> " << msg;
#endif

    if (msg.isEmpty())
        return;

    if (msg.length() <= 8)
    {
        _blockSizeJCOP = 1;
        return;
    }
    _blockSizeJCOP= 0;

    QString control = msg.left(2*4);
    QString data = msg.right(msg.length() - 8);

    doWriteOutput("JCP -> PC: " + control + " - " + data  +"\n");

    if (control.left(2) == "00")
    {
        //atr
        doWriteOutput("Connected to JCOP and reset card\n");

        JCOPAtr = data;
    }
    else if (control.left(2) == "01")
    {
        //response
        QString cmdToVICC = msg.right(msg.length() - 4);
        QByteArray array = QByteArray::fromHex(cmdToVICC.toLatin1());
        tcpSocketVCR->write(array);

        doWriteOutput("PC -> VICC: "+ array.toHex().toUpper() +"\n");
    }

}

void NewCardSession::doVCRDisconnected()
{
    isVCRConnected = false;
    doWriteOutput("VCR disconnected\n");

    if (isJCOPConnected)
        tcpSocketJCop->close();

    ui->connectPushButton->setText("Connect");
}

void NewCardSession::doJCOPDisconnected()
{
    isJCOPConnected = false;
    doWriteOutput("JCOP disconnected\n");

    if (isVCRConnected)
        tcpSocketVCR->close();

    ui->connectPushButton->setText("Connect");
}

void NewCardSession::doVCRConnected()
{
    _blockSizeVCR = 0;

    isVCRConnected = true;

    doWriteOutput("VCR connected\n");

    if (isJCOPConnected)
        ui->connectPushButton->setText("Disconnect");
}

void NewCardSession::doJCOPConnected()
{
    bool ok = false;

    _blockSizeJCOP = 0;

    isJCOPConnected = true;

    doWriteOutput("JCOP connected, send reset command and now connecting the VCR\n");

    //sent reset to JCOP
    QString ResetCommandJcop = "0021000400000000";
    QByteArray array = QByteArray::fromHex(ResetCommandJcop.toLatin1());
    tcpSocketJCop->write(array);

    doWriteOutput("PC -> JCP: "+ array.toHex().toUpper() +"\n");

    tcpSocketVCR->connectToHost(QHostAddress::LocalHost, ui->VirtualCardReaderPortLineEdit->text().toInt(&ok, 10));

}

void NewCardSession::displayErrorVCR(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("JCopTool Proxy"),
                                 tr("The Virtual Card Reader was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("JCopTool Proxy"),
                                 tr("The connection was refused by the Virtual Card Reader. "
                                    "Make sure the server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("JCopTool Proxy"),
                                 tr("Virtual Card Reader, the following error occurred: %1.")
                                 .arg(tcpSocketVCR->errorString()));
    }
}


void NewCardSession::displayErrorJCOP(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("JCopTool Proxy"),
                                 tr("The JCopTool server was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("JCopTool Proxy"),
                                 tr("The connection was refused by the JCopTool server. "
                                    "Make sure the server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("JCopTool Proxy"),
                                 tr("JCopTool server, The following error occurred: %1.")
                                 .arg(tcpSocketJCop->errorString()));
    }
}

void NewCardSession::on_autoConnectCheckBox_clicked()
{
    if  (ui->autoConnectCheckBox->isChecked())
    {
        ui->connectPushButton->setEnabled(false);
    }
    else
    {
        ui->connectPushButton->setEnabled(true);
    }
}

QString NewCardSession::userFriendlyCurrentFile()
{

    return strippedName(curFile);
}


QString NewCardSession::strippedName(const QString &fullFileName)
{
    return curFile;
}
