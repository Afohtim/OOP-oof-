#include "timerwidget.h"
#include "ui_timerwidget.h"

TimerWidget::TimerWidget(int interval, QString name, QString ringtone_name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimerWidget)
{
    ui->setupUi(this);

    timer = new QTimer(this);

    timerInterval = interval;
    timerName = name;
    ringtoneName = ringtone_name;
    active = false;

    ui->nameLabel->setText(timerName);

    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
    connect(ui->changeModeButton, SIGNAL(clicked()), this, SLOT(changeMode()));
    connect(timer, SIGNAL(timeout()), this, SLOT(alarmAndStop()));

    QTimer* refreshTimer = new QTimer(this);
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(displayTime()));
    refreshTimer->start();

}

QString TimerWidget::msToStringTime(int ms)
{
    int hours = ms/1000/3600;
    int minutes = ms/1000/60 - hours * 60;
    int seconds = ms/1000 - hours * 3600 - minutes * 60;
    return QTime(hours, minutes, seconds).toString("hh:mm:ss");
}

TimerWidget::~TimerWidget()
{
    delete ui;
}

void TimerWidget::changeMode()
{
    if(active)
    {
        timer->stop();
        ui->changeModeButton->setText("Start");
        active = false;
    }
    else
    {
        start();
        ui->changeModeButton->setText("Stop");
        active = true;
    }
}

void TimerWidget::start()
{
    timer->start(timerInterval);
}

void TimerWidget::displayTime()
{
    int dispayedTime = timerInterval;
    if(active)
    {
        dispayedTime = timer->remainingTime();
    }
    ui->timeLabel->setText(msToStringTime(dispayedTime));
    group = ui->groupEdit->toPlainText();
}

void TimerWidget::alarmAndStop()
{
    emit alarm(timerName, ringtoneName);
    changeMode();
}

void TimerWidget::closeWindow()
{
    emit destruction(id);
    this->close();
}
