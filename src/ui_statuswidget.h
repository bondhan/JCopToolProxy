/********************************************************************************
** Form generated from reading UI file 'statuswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUSWIDGET_H
#define UI_STATUSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatusWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *uptimerLabel;

    void setupUi(QWidget *StatusWidget)
    {
        if (StatusWidget->objectName().isEmpty())
            StatusWidget->setObjectName(QStringLiteral("StatusWidget"));
        StatusWidget->resize(718, 33);
        StatusWidget->setMinimumSize(QSize(0, 33));
        StatusWidget->setMaximumSize(QSize(16777215, 33));
        horizontalLayout_2 = new QHBoxLayout(StatusWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(StatusWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        uptimerLabel = new QLabel(StatusWidget);
        uptimerLabel->setObjectName(QStringLiteral("uptimerLabel"));

        horizontalLayout->addWidget(uptimerLabel);

        horizontalLayout->setStretch(1, 5);

        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(StatusWidget);

        QMetaObject::connectSlotsByName(StatusWidget);
    } // setupUi

    void retranslateUi(QWidget *StatusWidget)
    {
        StatusWidget->setWindowTitle(QApplication::translate("StatusWidget", "Form", 0));
        label->setText(QApplication::translate("StatusWidget", "Elapsed Time:", 0));
        uptimerLabel->setText(QApplication::translate("StatusWidget", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class StatusWidget: public Ui_StatusWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUSWIDGET_H
