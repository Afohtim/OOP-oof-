#include "alarmwidget.h"
#include "ui_alarmwidget.h"

AlarmWidget::AlarmWidget(QTime alarm_time, QString name, QWidget *parent):
    QDialog(parent),
    ui(new Ui::AlarmWidget)
{
    ui->setupUi(this);

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
    alarmTimer->start(alarmTime->elapsed());
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
    emit alarm();
    changeMode();
}

void AlarmWidget::closeWindow()
{
    emit destruction();
    this->close();
}
