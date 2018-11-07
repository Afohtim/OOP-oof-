#ifndef NEWALARMWINDOW_H
#define NEWALARMWINDOW_H

#include "ringtonedialog.h"
#include <QDialog>

namespace Ui {
class NewAlarmWindow;
}

class NewAlarmWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewAlarmWindow(QWidget *parent = nullptr);
    ~NewAlarmWindow();

private:
    Ui::NewAlarmWindow *ui;
    QString ringtoneName;
private slots:
    void sendInfoAndClose();
    void openRingtones();
    void setRingtone(QString);
signals:
    void sendAlarmInfo(int, QString, bool);

};

#endif // NEWALARMWINDOW_H
