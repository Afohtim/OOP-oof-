#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidget>
#include <QVBoxLayout>
#include <QString>
#include <fstream>
#include <string>
#include <sstream>

using std::ifstream;
using std::ofstream;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    subwidgetSize = 155;
    isMuted = false;

    nextAlarmId = nextTimerId = 0;

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
    connect(ui->startGroupButton, SIGNAL(clicked()), this, SLOT(startGroup()));
    connect(ui->stopGroupButton, SIGNAL(clicked()), this, SLOT(stopGroup()));
    connect(ui->alarmFilterButton, SIGNAL(clicked()), this, SLOT(filterAlarm()));
    connect(ui->alarmFilterDisableButton, SIGNAL(clicked()), this, SLOT(disableFilterAlarm()));


    ifstream fin("config.txt");
    std::string s;
    while(std::getline(fin, s))
    {
        if(!fin.good())
            break;
        std::stringstream stringin(s);
        std::string type, name, ringName;
        int ms;
        stringin >> type >> ringName >> ms >> name;
        if(type == "alarm")
        {
            int isOn;
            std::string group;
            stringin >> isOn >> group;
            addAlarmToList(ms, QString::fromStdString(ringName), isOn, QString::fromStdString(name));
            alarmWidgets.back()->setGroup(QString::fromStdString(group));

        }
        else if (type == "timer")
        {
            std::string group;
            stringin >> group;
            addTimerToList(ms, QString::fromStdString(ringName), false, QString::fromStdString(name));
            timerWidgets.back()->setGroup(QString::fromStdString(group));
        }
    }


    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start();
}

MainWindow::~MainWindow()
{
    ofstream fout("config.txt");
    for(auto timer : timerWidgets)
    {
        fout << "timer" << ' ' << timer->ringtoneName.toStdString() << ' ' << timer->ms << ' ' << timer->timerName.toStdString() << ' ' << timer->group.toStdString() << '\n';
    }

    for(auto alarm : alarmWidgets)
    {
        fout << "alarm" << ' ' << alarm->ringtoneName.toStdString() << ' ' << alarm->ms << ' ' << alarm->alarmName.toStdString() << ' ' << alarm->active << ' ' << alarm->group.toStdString() << '\n';
    }
}

void MainWindow::updateTime()
{
    ui->label->setText(QTime::currentTime().toString("hh:mm:ss AP"));
    alarmScrollWidget->setMinimumHeight(currentAlarms * subwidgetSize);
    timerScrollWidget->setMinimumHeight(currentTimers * subwidgetSize);
}

void MainWindow::newTimerSetup()
{
    auto timerSetupWindow = new NewTimerDialog(this);
    connect(timerSetupWindow, SIGNAL(sendTimerInfo(int, QString, bool, QString)), this, SLOT(addTimerToList(int, QString, bool, QString)));
    timerSetupWindow->exec();
}

void MainWindow::newAlarmSetup()
{
    auto alarmSetupWindow = new NewAlarmWindow(this);
    connect(alarmSetupWindow, SIGNAL(sendAlarmInfo(int, QString, bool, QString)), this, SLOT(addAlarmToList(int, QString, bool, QString)));
    alarmSetupWindow->exec();
}

void MainWindow::addTimerToList(int timeLeft, QString ringName, bool startNow, QString name)
{
    auto timerWidget = new TimerWidget(timeLeft, name, ringName, this);
    timerWidget->id = nextTimerId++;
    currentTimers++;
    if(startNow)
    {
        timerWidget->changeMode();
    }
    timerScrollWidget->layout()->addWidget(timerWidget);
    timerWidgets.push_back(timerWidget);
    connect(timerWidget, SIGNAL(destruction(int)), this, SLOT(timerDeletion(int)));
    connect(timerWidget, SIGNAL(alarm(QString, QString)), this, SLOT(timerAlarm(QString, QString)));

}

void MainWindow::addAlarmToList(int alarmTime, QString ringName, bool startNow, QString name)
{
    int hours = alarmTime/1000/3600;
    int minutes = alarmTime/1000/60 - hours * 60;
    int seconds = alarmTime/1000 - hours * 3600 - minutes * 60;
    QTime alarm_time = QTime(hours, minutes, seconds);
    auto alarmWidget = new AlarmWidget(alarm_time, name, ringName, this);
    alarmWidget->id = nextAlarmId++;
    currentAlarms++;
    if(startNow)
    {
        alarmWidget->changeMode();
    }

    alarmScrollWidget->layout()->addWidget(alarmWidget);
    alarmWidgets.push_back(alarmWidget);
    connect(alarmWidget, SIGNAL(destruction(int)), this, SLOT(alarmDeletion(int)));
    connect(alarmWidget, SIGNAL(alarm(QString, QString)), this, SLOT(alarm(QString, QString)));
}

QString MainWindow::msToStringTime(int ms)
{
    int hours = ms/1000/3600;
    int minutes = ms/1000/60 - hours * 60;
    int seconds = ms/1000 - hours * 3600 - minutes * 60;
    return QTime(hours, minutes, seconds).toString("hh:mm:ss");
}

void MainWindow::timerDeletion(int id)
{

    for(unsigned i = 0; i < timerWidgets.size(); ++i)
    {
        if(timerWidgets[i]->id == id)
        {
            timerWidgets.erase(timerWidgets.begin() + i);
            break;
        }
    }
    currentTimers--;
}

void MainWindow::alarmDeletion(int id)
{
    for(unsigned i = 0; i < alarmWidgets.size(); ++i)
    {
        if(alarmWidgets[i]->id == id)
        {
            alarmScrollWidget->layout()->removeWidget(alarmWidgets[i]);
            alarmWidgets.erase(alarmWidgets.begin() + i);
            break;
        }
    }
    currentAlarms--;
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

void MainWindow::startGroup()
{
    for(auto timer : timerWidgets)
    {
        if(timer->group == ui->groupEdit->toPlainText())
        {
            if(!timer->active)
            {
                timer->changeMode();
            }
        }
    }

    for(auto alarm : alarmWidgets)
    {
        if(alarm->group == ui->groupEdit->toPlainText())
        {
            if(!alarm->active)
            {
                alarm->changeMode();
            }
        }
    }
}

void MainWindow::stopGroup()
{
    for(auto timer : timerWidgets)
    {
        if(timer->group == ui->groupEdit->toPlainText())
        {
            if(timer->active)
            {
                timer->changeMode();
            }
        }
    }

    for(auto alarm : alarmWidgets)
    {
        if(alarm->group == ui->groupEdit->toPlainText())
        {
            if(alarm->active)
            {
                alarm->changeMode();
            }
        }
    }
}

void MainWindow::filterAlarm()
{
    for(int i = 0; i < alarmScrollWidget->layout()->count(); ++i)
    {
        alarmScrollWidget->layout()->itemAt(i)->widget()->hide();
    }
    currentAlarms = 0;

    for(int i = 0; i < alarmScrollWidget->layout()->count(); ++i)
    {
        auto alarm = alarmWidgets[i];
        if(alarm->ms >= ui->fromAlarm->time().msecsSinceStartOfDay() && alarm->ms <= ui->toAlarm->time().msecsSinceStartOfDay() )
        {
            alarmScrollWidget->layout()->itemAt(i)->widget()->show();
            currentAlarms++;
        }
    }

}

void MainWindow::disableFilterAlarm()
{
    for(int i = 0; i < alarmScrollWidget->layout()->count(); ++i)
    {
        alarmScrollWidget->layout()->itemAt(i)->widget()->show();
    }
    currentAlarms = alarmScrollWidget->layout()->count();
}



