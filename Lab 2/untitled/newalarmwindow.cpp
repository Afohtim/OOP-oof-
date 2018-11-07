#include "newalarmwindow.h"
#include "ui_newalarmwindow.h"

NewAlarmWindow::NewAlarmWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAlarmWindow)
{
    ui->setupUi(this);

    connect(ui->confirmButton, SIGNAL(clicked()), this, SLOT(sendInfoAndClose()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

NewAlarmWindow::~NewAlarmWindow()
{
    delete ui;
}

void NewAlarmWindow::sendInfoAndClose()
{
    QTime triggerTime = ui->timeSet->time();
    emit sendAlarmInfo(triggerTime.msecsSinceStartOfDay());
    this->close();
}
