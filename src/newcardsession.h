#ifndef NEWCARDSESSION_H
#define NEWCARDSESSION_H

#include <winscard.h>
#include <QWidget>
#include <QTcpSocket>
#include <QCloseEvent>
#include <QTextEdit>
#include"simplepcscmanager.h"
#include <QMutex>

#define TIMER_INTERVAL      100

namespace Ui {
class NewCardSession;

}

class NewCardSession : public QWidget
{
    Q_OBJECT

public:
    explicit NewCardSession(QWidget *parent = 0);
    ~NewCardSession();
    bool save();
    bool saveAs();
    QTextEdit *getOutputWindow();
    QString curFile;
    QString userFriendlyCurrentFile();
    void setAutoChecked(bool);

private:
    //    LONG doListCardReaders();
    void doWriteOutput(QString text);
    bool isVCRConnected;
    bool isJCOPConnected;
    QString JCOPAtr;
    bool was000102;
    quint16 _blockSizeVCR;
    quint16 _blockSizeJCOP;

    QByteArray arrayVCR;
    QByteArray arrayJCOP;
    QTimer *loadingTimer;

    int str001000A404000BA0000003974349445F0100;
    int str000500CA7F6800;
    int str000E00A4040009A00000030800001000;
    int str000E00A4040009A00000039742544659;

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void doAutoCheck();
    void on_clearPushButton_clicked();
    void readyCopyAvailable(bool);

    void on_connectPushButton_clicked();
    void displayErrorVCR(QAbstractSocket::SocketError socketError);
    void displayErrorJCOP(QAbstractSocket::SocketError socketError);

    void doVCRDisconnected();
    void doJCOPDisconnected();
    void doVCRConnected();
    void doJCOPConnected();
    void doVCRRead();
    void doJCOPRead();

    bool cleanUp();

    void on_autoConnectCheckBox_clicked();

    QString strippedName(const QString &fullFileName);

    void populateCardReaders();

signals:
    void copyAvailable(bool);

private:
    Ui::NewCardSession *ui;

    QTcpSocket *tcpSocketVCR;
    QTcpSocket *tcpSocketJCop;
};

#endif // NEWCARDSESSION_H
