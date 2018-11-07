#ifndef NEWALARMWINDOW_H
#define NEWALARMWINDOW_H

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
private slots:
    void sendInfoAndClose();
signals:
    void sendAlarmInfo(int);

};

#endif // NEWALARMWINDOW_H
