#include "ringtonedialog.h"
#include "ui_ringtonedialog.h"

RingtoneDialog::RingtoneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RingtoneDialog)
{
    ui->setupUi(this);

    ui->ringtoneList->addItem("ringtone 1");
    ui->ringtoneList->addItem("ringtone 2");
    ui->ringtoneList->addItem("ringtone 3");
    ui->ringtoneList->addItem("ringtone 4");
    player = new QMediaPlayer;

    connect(ui->ringtoneList,SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(play(QListWidgetItem*)));
    connect(ui->ringtoneList,SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(select(QListWidgetItem*)));
}

RingtoneDialog::~RingtoneDialog()
{
    delete ui;
}

void RingtoneDialog::play(QListWidgetItem* item)
{
    QString ringtoneName = item->text();
    if(ringtoneName == "ringtone 1")
    {
        player->setMedia(QUrl::fromLocalFile("../untitled/data/beep_boop.mp3"));
    }
    else if(ringtoneName == "ringtone 2")
    {
        player->setMedia(QUrl::fromLocalFile("../untitled/data/2.mp3"));
    }
    else if(ringtoneName == "ringtone 3")
    {
        player->setMedia(QUrl::fromLocalFile("../untitled/data/3.mp3"));
    }
    else if(ringtoneName == "ringtone 4")
    {
        player->setMedia(QUrl::fromLocalFile("../untitled/data/4.mp3"));
    }
    player->play();
}

void RingtoneDialog::select(QListWidgetItem* item)
{
    QString ringtoneName = item->text();
    if(ringtoneName == "ringtone 1")
    {
        emit ringtoneSelected("../untitled/data/beep_boop.mp3");
    }
    else if(ringtoneName == "ringtone 2")
    {
        emit ringtoneSelected("../untitled/data/2.mp3");
    }
    else if(ringtoneName == "ringtone 3")
    {
        emit ringtoneSelected("../untitled/data/3.mp3");
    }
    else if(ringtoneName == "ringtone 4")
    {
        emit ringtoneSelected("../untitled/data/4.mp3");
    }
    delete player;
    this->close();
}
