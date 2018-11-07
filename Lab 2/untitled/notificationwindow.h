#ifndef NOTIFICATIONWINDOW_H
#define NOTIFICATIONWINDOW_H

#include <QDialog>
#include <QMediaPlaylist>
#include <QMediaPlayer>

namespace Ui {
class NotificationWindow;
}

class NotificationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NotificationWindow(QString message, bool muted, QString ringtoneName, QWidget *parent = nullptr);
    ~NotificationWindow();

private:
    QMediaPlayer* player;
    Ui::NotificationWindow *ui;
private slots:
    void closeWindow();
};

#endif // NOTIFICATIONWINDOW_H
