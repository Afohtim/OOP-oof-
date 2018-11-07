#include "alarmwidget.h"
#include "ui_alarmwidget.h"

AlarmWidget::AlarmWidget(QTime alarm_time, QString name, QWidget *parent):
    QDialog(parent),
    ui(new Ui::AlarmWidget)
{
    ui->setupUi(this);

    ui->nameLabel->setText(name);
    alarmTimer = new QTimer(this);
    alarmTime = new QTime(alarm_time.hour(), alarm_time.minute(), alarm_time.second());
    alarmName = name;
    active = false;
    ui->timeLabel->setText(alarmTime->toString("hh:mm AP"));

    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
    connect(ui->changeModeButton, SIGNAL(clicked()), this, SLOT(changeMode()));
    connect(alarmTimer, SIGNAL(timeout()), this, SLOT(alarmAndStop()));

}

AlarmWidget::~AlarmWidget()
{
    emit destruction();
    delete ui;
}


void AlarmWidget::start()
{
    int timerLength = alarmTime->msecsSinceStartOfDay() - QTime::currentTime().msecsSinceStartOfDay();
    if(timerLength < 0)
    {
        timerLength += 24 * 3600 * 1000;
    }
    timerLength += 1000;
    alarmTimer->start(timerLength);
}

void AlarmWidget::changeMode()
{
    if(active)
    {
        alarmTimer->stop();
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

void AlarmWidget::alarmAndStop()
{
    emit alarm(alarmName);
    changeMode();
}

void AlarmWidget::closeWindow()
{
    emit destruction();
    this->close();
}
