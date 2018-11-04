#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "newtimerwindow.h"
#include <vector>
#include <QMainWindow>
#include <QTimer>
#include <QTime>
//#include <QString>

using std::vector;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void test();

private:
    Ui::MainWindow *ui;
    QString time;
    vector<QTimer*> timers;
    QWidget* timersWidget;

    QString msToStringTime(int ms);


private slots:
    void updateTime();
    void newTimerSetup();
    void addTimerToList(int);

};

#endif // MAINWINDOW_H
