#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "newtimerwindow.h"
#include "timerwidget.h"
#include "alarmwidget.h"
#include "newalarmwindow.h"
#include "notificationwindow.h"

#include <vector>
#include <QMainWindow>
#include <QTimer>
#include <QTime>

using std::vector;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void test();

private:
    Ui::MainWindow *ui;
    vector<QTimer*> timers;
    QWidget* timerScrollWidget;
    QWidget* alarmScrollWidget;
    QString msToStringTime(int);
    int subwidgetSize;
    bool isMuted;
    vector<TimerWidget*> timerWidgets;
    int nextTimerId;
    vector<AlarmWidget*> alarmWidgets;
    int nextAlarmId;
    int currentTimers = 0;
    int currentAlarms = 0;


private slots:
    void updateTime();
    void newTimerSetup();
    void newAlarmSetup();
    void addTimerToList(int, QString, bool);
    void addAlarmToList(int, QString, bool);
    void timerDeletion(int);
    void alarmDeletion(int);
    void alarm(QString, QString);
    void timerAlarm(QString, QString);
    void switchMute();
    void startGroup();
    void stopGroup();

};

#endif // MAINWINDOW_H
