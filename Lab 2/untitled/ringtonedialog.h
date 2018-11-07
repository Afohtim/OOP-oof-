#ifndef RINGTONEDIALOG_H
#define RINGTONEDIALOG_H

#include <QDialog>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QListWidgetItem>

namespace Ui {
class RingtoneDialog;
}

class RingtoneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RingtoneDialog(QWidget *parent = nullptr);
    ~RingtoneDialog();

private:
    Ui::RingtoneDialog *ui;
    QMediaPlayer* player;
private slots:
    void play(QListWidgetItem*);
    void select(QListWidgetItem*);
signals:
    void ringtoneSelected(QString);
};

#endif // RINGTONEDIALOG_H
