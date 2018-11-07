#ifndef NEWTIMERWINDOW_H
#define NEWTIMERWINDOW_H


#include "ringtonedialog.h"
#include <QDialog>

namespace Ui {
class NewTimerDialog;
}

class NewTimerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTimerDialog(QWidget *parent = nullptr);
    ~NewTimerDialog();

private:
    Ui::NewTimerDialog *ui;
    QString ringtoneName;
private slots:
    void sendInfoAndClose();
    void openRingtones();
    void setRingtone(QString);
signals:
    void sendTimerInfo(int, QString, bool);

};

#endif // NEWTIMERWINDOW_H
