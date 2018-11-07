#include "newalarmwindow.h"
#include "ui_newalarmwindow.h"

NewAlarmWindow::NewAlarmWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAlarmWindow)
{
    ui->setupUi(this);

    ringtoneName = "../untitled/data/beep_boop.mp3";
    connect(ui->confirmButton, SIGNAL(clicked()), this, SLOT(sendInfoAndClose()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->ringtoneButton, SIGNAL(clicked()), this, SLOT(openRingtones()));
}

NewAlarmWindow::~NewAlarmWindow()
{
    delete ui;
}

void NewAlarmWindow::sendInfoAndClose()
{
    QTime triggerTime = ui->timeSet->time();
    emit sendAlarmInfo(triggerTime.msecsSinceStartOfDay(), ringtoneName, ui->startBox->isChecked());
    this->close();
}

void NewAlarmWindow::openRingtones()
{
    RingtoneDialog* wind = new RingtoneDialog(this);
    connect(wind, SIGNAL(ringtoneSelected(QString)), this, SLOT(setRingtone(QString)));
    wind->exec();
}

void NewAlarmWindow::setRingtone(QString name)
{
    ringtoneName = name;
}
