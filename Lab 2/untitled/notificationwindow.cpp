#include "notificationwindow.h"
#include "ui_notificationwindow.h"

NotificationWindow::NotificationWindow(QString message, bool muted, QString ringtoneName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotificationWindow)
{
    ui->setupUi(this);
    ui->message->setText(message);
    player = new QMediaPlayer;
    if(!muted)
    {
        auto playlist = new QMediaPlaylist();
        playlist->addMedia(QUrl::fromLocalFile(ringtoneName));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);

        player->setPlaylist(playlist);
        player->setVolume(100);
        player->play();
    }

    connect(ui->OkButton, SIGNAL(clicked()), this, SLOT(closeWindow()));

}

NotificationWindow::~NotificationWindow()
{
    delete ui;
}

void NotificationWindow::closeWindow()
{
    delete player;
    this->close();
}
