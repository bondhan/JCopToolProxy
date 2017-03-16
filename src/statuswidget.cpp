#include "statuswidget.h"
#include "ui_statuswidget.h"

#ifdef SHOW_DEBUG
#include <QDebug>
#endif

int StatusWidget::hours = 0;
int StatusWidget::minutes = 0;
int StatusWidget::seconds = 0;
int StatusWidget::days = 0;

StatusWidget::StatusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusWidget)
{
    ui->setupUi(this);

    timer.setInterval(1000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(showTimeElapsed()));

    elapsedTimer.start();
    timer.start();

#ifdef SHOW_DEBUG
    qDebug() << "The slow operation took" << elapsedTimer.elapsed() << "milliseconds";
#endif
}

void StatusWidget::showTimeElapsed()
{
    seconds++;

    if (seconds >= 60)
    {
        minutes++;
        seconds = 0;
    }

    if (minutes >= 60)
    {
        hours++;
        minutes = 0;
    }

    if (hours >= 24)
    {
        days++;
        hours = 0;
    }

    ui->uptimerLabel->setText(" Day: " + QString::number(days,10) +
                              " H: " + QString::number(hours,10) +
                              " M: " + QString::number(minutes,10) +
                              " S: " + QString::number(seconds,10));
    this->setMaximumHeight(30);
    this->setMinimumHeight(30);
}

StatusWidget::~StatusWidget()
{
    delete ui;
}



