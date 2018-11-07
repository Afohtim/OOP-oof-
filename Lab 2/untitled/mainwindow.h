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
//#include <QString>

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
    int scrollTimerWidgetSize = 0;
    int scrollAlarmWidgetSize = 0;
    int subwidgetSize;


private slots:
    void updateTime();
    void newTimerSetup();
    void newAlarmSetup();
    void addTimerToList(int);
    void addAlarmToList(int);
    void timerDeletion();
    void alarmDeletion();
    void alarm(QString);
    void timerAlarm(QString);


};

#endif // MAINWINDOW_H
