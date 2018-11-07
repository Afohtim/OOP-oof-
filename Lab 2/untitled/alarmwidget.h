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
    explicit AlarmWidget(QTime inetrval, QString name, QWidget *parent = nullptr);
    ~AlarmWidget();

private:
    Ui::AlarmWidget *ui;
    QTime* alarmTime;
    QTimer* alarmTimer;
    QString alarmName;
    bool active;

private slots:
    void start();
    void changeMode();
    void alarmAndStop();

    void closeWindow();

signals:
    void alarm(QString);
    void destruction();
};

#endif // ALARMWIDGET_H
