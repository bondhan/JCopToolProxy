#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>
#include <QElapsedTimer>
#include <QTimer>

namespace Ui {
class StatusWidget;
}

class StatusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatusWidget(QWidget *parent = 0);
    ~StatusWidget();


private:
    Ui::StatusWidget *ui;
    QElapsedTimer elapsedTimer;
    QTimer timer;
    static int hours;
    static int minutes;
    static int seconds;
    static int days;

public slots:
    void showTimeElapsed(void);


};

#endif // STATUSWIDGET_H
