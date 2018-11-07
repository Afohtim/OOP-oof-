#include "alarmwidget.h"
#include "ui_alarmwidget.h"

AlarmWidget::AlarmWidget(QTime alarm_time, QString name, QString ringtone_name, QWidget *parent):
    QDialog(parent),
    ui(new Ui::AlarmWidget)
{
    ui->setupUi(this);

    ui->nameLabel->setText(name);
    alarmTimer = new QTimer(this);
    alarmTime = new QTime(alarm_time.hour(), alarm_time.minute(), alarm_time.second());
    alarmName = name;
    ringtoneName = ringtone_name;
    active = false;
    ui->timeLabel->setText(alarmTime->toString("hh:mm AP"));

    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
    connect(ui->changeModeButton, SIGNAL(clicked()), this, SLOT(changeMode()));
    connect(alarmTimer, SIGNAL(timeout()), this, SLOT(alarmAndStop()));

    QTimer* refreshTimer = new QTimer(this);
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(displayTime()));
    refreshTimer->start();

}

AlarmWidget::~AlarmWidget()
{
    emit destruction(id);
    delete ui;
}

void AlarmWidget::displayTime()
{
    group = ui->groupEdit->toPlainText();
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
    emit alarm(alarmName, ringtoneName);
    changeMode();
}

void AlarmWidget::closeWindow()
{
    emit destruction(id);
    this->close();
}
