#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QListWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timerWidgetSize = 115;
    timerScrollWidget = new QWidget;
    timerScrollWidget->setLayout(new QVBoxLayout(this));
    timerScrollWidget->setMinimumHeight(200);
    ui->timerWidgets->setWidget(timerScrollWidget);

    ui->closeButton->setText("Close");
    connect(ui->closeButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(ui->newTimerButton, SIGNAL(clicked()), this, SLOT(newTimerSetup()));

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    ui->label->setText(QTime::currentTime().toString("hh:mm:ss AP"));
}

void MainWindow::newTimerSetup()
{
    auto timerSetupWindow = new NewTimerDialog(this);
    connect(timerSetupWindow, SIGNAL(sendTimerInfo(int)), this, SLOT(addTimerToList(int)));
    timerSetupWindow->exec();
}

void MainWindow::addTimerToList(int timeLeft)
{
    QString time = msToStringTime(timeLeft);
    auto timerWidget = new TimerWidget(timeLeft, QString("timer"), this);
    scrollWidgetSize += timerWidgetSize;
    timerScrollWidget->setMinimumHeight(scrollWidgetSize);
    timerScrollWidget->layout()->addWidget(timerWidget);
}

QString MainWindow::msToStringTime(int ms)
{
    int hours = ms/1000/3600;
    int minutes = ms/1000/60 - hours * 60;
    int seconds = ms/1000 - hours * 3600 - minutes * 60;
    return QTime(hours, minutes, seconds).toString("hh:mm:ss");
}
