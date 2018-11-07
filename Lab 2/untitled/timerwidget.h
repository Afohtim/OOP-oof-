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
    explicit TimerWidget(int inetrval, QString name, QString ringtone_name, QWidget *parent = nullptr);
    ~TimerWidget();

private:
    Ui::TimerWidget *ui;
    QString msToStringTime(int ms);
    QTimer* timer;
    int timerInterval;
    QString timerName;
    QString ringtoneName;
    bool active;

private slots:
    void start();

    void displayTime();
    void alarmAndStop();
    void closeWindow();

public slots:
    void changeMode();

signals:
    void alarm(QString, QString);
    void destruction();

};

#endif // TIMER_H
