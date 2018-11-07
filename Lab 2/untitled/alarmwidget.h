#ifndef ALARMWIDGET_H
#define ALARMWIDGET_H

#include <QDialog>
#include <QTime>
#include <QTimer>

namespace Ui {
class AlarmWidget;
}

class AlarmWidget : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmWidget(QTime inetrval, QString name, QString ringtone_name, QWidget *parent = nullptr);
    ~AlarmWidget();

    QString group;
    int id;
    bool active;
    QString alarmName;
    int ms;

private:
    Ui::AlarmWidget *ui;
    QTime* alarmTime;
    QTimer* alarmTimer;
    QString ringtoneName;

private slots:
    void start();
    void alarmAndStop();

    void closeWindow();

public slots:
    void changeMode();
    void displayTime();


signals:
    void alarm(QString, QString);
    void destruction(int);
};

#endif // ALARMWIDGET_H
