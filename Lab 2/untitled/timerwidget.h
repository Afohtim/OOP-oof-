#ifndef TIMER_H
#define TIMER_H

#include <QDialog>
#include <QTime>
#include <QTimer>

namespace Ui {
class TimerWidget;
}

class TimerWidget : public QDialog
{
    Q_OBJECT

public:
    explicit TimerWidget(int inetrval, QString name, QWidget *parent = nullptr);
    ~TimerWidget();

private:
    Ui::TimerWidget *ui;
    QString msToStringTime(int ms);
    QTimer* timer;
    int timerInterval;
    QString timerName;
    bool active;

private slots:
    void start();
    void changeMode();

    void displayTime();
    void alarmAndStop();

    void closeWindow();

signals:
    void alarm();
    void destruction();

};

#endif // TIMER_H
