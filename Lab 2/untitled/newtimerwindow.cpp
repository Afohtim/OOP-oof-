#include "newtimerwindow.h"
#include "ui_newtimerwindow.h"

NewTimerDialog::NewTimerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTimerDialog)
{
    ui->setupUi(this);


    ringtoneName = QString("../untitled/data/beep_boop.mp3");
    connect(ui->confirmButton, SIGNAL(clicked()), this, SLOT(sendInfoAndClose()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->ringtoneButton, SIGNAL(clicked()), this, SLOT(openRingtones()));
}

NewTimerDialog::~NewTimerDialog()
{
    delete ui;
}

void NewTimerDialog::sendInfoAndClose()
{
    int elapcedTime = 1000*(ui->timeSet->time().hour()*3600 + ui->timeSet->time().minute()*60 + ui->timeSet->time().second());
    emit sendTimerInfo(elapcedTime, ringtoneName, ui->startBox->isChecked());
    this->close();
}


void NewTimerDialog::openRingtones()
{
    RingtoneDialog* wind = new RingtoneDialog(this);
    connect(wind, SIGNAL(ringtoneSelected(QString)), this, SLOT(setRingtone(QString)));
    wind->exec();
}

void NewTimerDialog::setRingtone(QString name)
{
    ringtoneName = name;
}
