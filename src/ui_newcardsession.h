/********************************************************************************
** Form generated from reading UI file 'newcardsession.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWCARDSESSION_H
#define UI_NEWCARDSESSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewCardSession
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *mainVerticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *VirtualCardReaderPortLineEdit;
    QLabel *label_2;
    QLineEdit *JCopPortLineEdit;
    QPushButton *connectPushButton;
    QCheckBox *autoConnectCheckBox;
    QPushButton *clearPushButton;
    QTextEdit *OutputTextEdit;

    void setupUi(QWidget *NewCardSession)
    {
        if (NewCardSession->objectName().isEmpty())
            NewCardSession->setObjectName(QStringLiteral("NewCardSession"));
        NewCardSession->resize(639, 399);
        horizontalLayout_2 = new QHBoxLayout(NewCardSession);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        mainVerticalLayout = new QVBoxLayout();
        mainVerticalLayout->setObjectName(QStringLiteral("mainVerticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(NewCardSession);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        VirtualCardReaderPortLineEdit = new QLineEdit(NewCardSession);
        VirtualCardReaderPortLineEdit->setObjectName(QStringLiteral("VirtualCardReaderPortLineEdit"));

        horizontalLayout->addWidget(VirtualCardReaderPortLineEdit);

        label_2 = new QLabel(NewCardSession);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        JCopPortLineEdit = new QLineEdit(NewCardSession);
        JCopPortLineEdit->setObjectName(QStringLiteral("JCopPortLineEdit"));

        horizontalLayout->addWidget(JCopPortLineEdit);

        connectPushButton = new QPushButton(NewCardSession);
        connectPushButton->setObjectName(QStringLiteral("connectPushButton"));

        horizontalLayout->addWidget(connectPushButton);

        autoConnectCheckBox = new QCheckBox(NewCardSession);
        autoConnectCheckBox->setObjectName(QStringLiteral("autoConnectCheckBox"));

        horizontalLayout->addWidget(autoConnectCheckBox);

        clearPushButton = new QPushButton(NewCardSession);
        clearPushButton->setObjectName(QStringLiteral("clearPushButton"));

        horizontalLayout->addWidget(clearPushButton);

        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(3, 1);

        mainVerticalLayout->addLayout(horizontalLayout);

        OutputTextEdit = new QTextEdit(NewCardSession);
        OutputTextEdit->setObjectName(QStringLiteral("OutputTextEdit"));

        mainVerticalLayout->addWidget(OutputTextEdit);


        horizontalLayout_2->addLayout(mainVerticalLayout);


        retranslateUi(NewCardSession);

        QMetaObject::connectSlotsByName(NewCardSession);
    } // setupUi

    void retranslateUi(QWidget *NewCardSession)
    {
        NewCardSession->setWindowTitle(QApplication::translate("NewCardSession", "Card Session", 0));
        label_3->setText(QApplication::translate("NewCardSession", "Card ReaderPort:", 0));
#ifndef QT_NO_TOOLTIP
        VirtualCardReaderPortLineEdit->setToolTip(QApplication::translate("NewCardSession", "Port Number of the virtual card reader", 0));
#endif // QT_NO_TOOLTIP
        VirtualCardReaderPortLineEdit->setText(QApplication::translate("NewCardSession", "35963", 0));
        label_2->setText(QApplication::translate("NewCardSession", "JCopTool Port:", 0));
#ifndef QT_NO_TOOLTIP
        JCopPortLineEdit->setToolTip(QApplication::translate("NewCardSession", "JCOP port number", 0));
#endif // QT_NO_TOOLTIP
        JCopPortLineEdit->setText(QApplication::translate("NewCardSession", "8050", 0));
        connectPushButton->setText(QApplication::translate("NewCardSession", "Connect", 0));
#ifndef QT_NO_TOOLTIP
        autoConnectCheckBox->setToolTip(QApplication::translate("NewCardSession", "Wait for the JCOP port to be ready automatically", 0));
#endif // QT_NO_TOOLTIP
        autoConnectCheckBox->setText(QApplication::translate("NewCardSession", "Auto", 0));
        clearPushButton->setText(QApplication::translate("NewCardSession", "Clear", 0));
    } // retranslateUi

};

namespace Ui {
    class NewCardSession: public Ui_NewCardSession {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCARDSESSION_H
