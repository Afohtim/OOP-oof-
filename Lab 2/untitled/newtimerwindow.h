#ifndef NEWTIMERWINDOW_H
#define NEWTIMERWINDOW_H

#include <QDialog>

namespace Ui {
class NewTimerWindow;
}

class NewTimerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewTimerWindow(QWidget *parent = nullptr);
    ~NewTimerWindow();

private:
    Ui::NewTimerWindow *ui;
};

#endif // NEWTIMERWINDOW_H
