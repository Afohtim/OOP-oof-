#include "newtimerwindow.h"
#include "ui_newtimerwindow.h"

NewTimerDialog::NewTimerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTimerDialog)
{
    ui->setupUi(this);

    ui->hoursLabel->setText("hours");
    ui->minutesLabel->setText("minutes");
    ui->secondsLabel->setText("seconds");

    connect(ui->confirmButton, SIGNAL(clicked()), this, SLOT(sendInfoAndClose()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

NewTimerDialog::~NewTimerDialog()
{
    delete ui;
}

void NewTimerDialog::sendInfoAndClose()
{
    int elapcedTime = 1000*(ui->timeSet->time().hour()*3600 + ui->timeSet->time().minute()*60 + ui->timeSet->time().second());
    emit sendTimerInfo(elapcedTime);
    this->close();
}
