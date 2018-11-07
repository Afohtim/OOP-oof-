#include "notificationwindow.h"
#include "ui_notificationwindow.h"

NotificationWindow::NotificationWindow(QString message, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NotificationWindow)
{
    ui->setupUi(this);
    ui->message->setText(message);

    auto playlist = new QMediaPlaylist();
    //change to read from local dir
    playlist->addMedia(QUrl::fromLocalFile("../untitled/data/beep_boop.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player = new QMediaPlayer;
    player->setPlaylist(playlist);
    player->setVolume(100);
    player->play();
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
