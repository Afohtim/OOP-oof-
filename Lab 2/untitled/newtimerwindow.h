#ifndef NEWTIMERWINDOW_H
#define NEWTIMERWINDOW_H

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
private slots:
    void sendInfoAndClose();
signals:
    void sendTimerInfo(int);

};

#endif // NEWTIMERWINDOW_H
