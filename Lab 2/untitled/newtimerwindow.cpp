#include "newtimerwindow.h"
#include "ui_newtimerwindow.h"

NewTimerWindow::NewTimerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTimerWindow)
{
    ui->setupUi(this);
}

NewTimerWindow::~NewTimerWindow()
{
    delete ui;
}
