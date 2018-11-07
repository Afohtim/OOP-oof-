#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    subwidgetSize = 115;
    isMuted = false;

    timerScrollWidget = new QWidget;
    timerScrollWidget->setLayout(new QVBoxLayout(this));
    timerScrollWidget->setMinimumHeight(200);
    ui->timerWidgets->setWidget(timerScrollWidget);

    alarmScrollWidget = new QWidget;
    alarmScrollWidget->setLayout(new QVBoxLayout(this));
    alarmScrollWidget->setMinimumHeight(200);
    ui->alarmWidgets->setWidget(alarmScrollWidget);

    ui->closeButton->setText("Close");
    connect(ui->closeButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(ui->newTimerButton, SIGNAL(clicked()), this, SLOT(newTimerSetup()));
    connect(ui->newAlarmButton, SIGNAL(clicked()), this, SLOT(newAlarmSetup()));
    connect(ui->muteButton, SIGNAL(clicked()), this, SLOT(switchMute()));

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    ui->label->setText(QTime::currentTime().toString("hh:mm:ss AP"));
}

void MainWindow::newTimerSetup()
{
    auto timerSetupWindow = new NewTimerDialog(this);
    connect(timerSetupWindow, SIGNAL(sendTimerInfo(int, QString, bool)), this, SLOT(addTimerToList(int, QString, bool)));
    timerSetupWindow->exec();
}

void MainWindow::newAlarmSetup()
{
    auto alarmSetupWindow = new NewAlarmWindow(this);
    connect(alarmSetupWindow, SIGNAL(sendAlarmInfo(int, QString, bool)), this, SLOT(addAlarmToList(int, QString, bool)));
    alarmSetupWindow->exec();
}

void MainWindow::addTimerToList(int timeLeft, QString ringName, bool startNow)
{
    auto timerWidget = new TimerWidget(timeLeft, QString("timer"), ringName, this);
    if(startNow)
    {
        timerWidget->changeMode();
    }

    scrollTimerWidgetSize += subwidgetSize;
    timerScrollWidget->setMinimumHeight(scrollTimerWidgetSize);
    timerScrollWidget->layout()->addWidget(timerWidget);
    connect(timerWidget, SIGNAL(destruction()), this, SLOT(timerDeletion()));
    connect(timerWidget, SIGNAL(alarm(QString, QString)), this, SLOT(timerAlarm(QString, QString)));

}

void MainWindow::addAlarmToList(int alarmTime, QString ringName, bool startNow)
{
    int hours = alarmTime/1000/3600;
    int minutes = alarmTime/1000/60 - hours * 60;
    int seconds = alarmTime/1000 - hours * 3600 - minutes * 60;
    QTime alarm_time = QTime(hours, minutes, seconds);
    auto alarmWidget = new AlarmWidget(alarm_time, QString("alarm"), ringName, this);
    if(startNow)
    {
        alarmWidget->changeMode();
        system("pause");
    }

    scrollAlarmWidgetSize += subwidgetSize;
    alarmScrollWidget->setMinimumHeight(scrollAlarmWidgetSize);
    alarmScrollWidget->layout()->addWidget(alarmWidget);
    connect(alarmWidget, SIGNAL(destruction()), this, SLOT(alarmDeletion()));
    connect(alarmWidget, SIGNAL(alarm(QString, QString)), this, SLOT(alarm(QString, QString)));
}

QString MainWindow::msToStringTime(int ms)
{
    int hours = ms/1000/3600;
    int minutes = ms/1000/60 - hours * 60;
    int seconds = ms/1000 - hours * 3600 - minutes * 60;
    return QTime(hours, minutes, seconds).toString("hh:mm:ss");
}

void MainWindow::timerDeletion()
{
    scrollTimerWidgetSize -= subwidgetSize;
    timerScrollWidget->setMinimumHeight(scrollTimerWidgetSize);
}

void MainWindow::alarmDeletion()
{
    scrollAlarmWidgetSize -= subwidgetSize;
    alarmScrollWidget->setMinimumHeight(scrollAlarmWidgetSize);
}

void MainWindow::timerAlarm(QString message, QString ringtoneName)
{
    auto wind = new NotificationWindow(message, isMuted, ringtoneName, this);
    wind->exec();
}

void MainWindow::alarm(QString message, QString ringtoneName)
{
    auto wind = new NotificationWindow(message + "\n" +QTime::currentTime().toString("hh:mm AP"), isMuted, ringtoneName, this);
    wind->exec();
}

void MainWindow::switchMute()
{
    if(isMuted)
    {
        ui->muteButton->setText("Mute");
        isMuted = false;
    }
    else
    {
        ui->muteButton->setText("Unmute");
        isMuted = true;
    }



}

