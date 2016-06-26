#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Breed;
class Chest;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(Breed *player, Chest *chest, QWidget *parent = 0);
    ~Dialog();
    void paintEvent(QPaintEvent *);
    void leftButtonVerify();
    void rightButtonVerify();
    bool canEquipItem();

private slots:
    void on_equipRightHand_clicked();

    void on_equipLeftHand_clicked();

private:
    Ui::Dialog *ui;
    Breed *player;
    Chest *chest;
};

#endif // DIALOG_H
