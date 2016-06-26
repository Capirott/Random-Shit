#include "dialog.h"
#include "ui_dialog.h"

#include "Class/Pieces/chest.h"
#include "Class/Pieces/Targets/breed.h"
#include "Class/Pieces/Items/onehandeditem.h"

#include <QPainter>

Dialog::Dialog(Breed *player, Chest *chest, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    this->chest = chest;
    this->player = player;
    ui->setupUi(this);
    setWindowTitle("OpenChest");
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setModal(true);
    setFixedSize(450, 350);
    leftButtonVerify();
    rightButtonVerify();
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::canEquipItem()
{

    OneHandedItem *chestItem = (OneHandedItem *)chest->getItem();

    if (chestItem)
    {
        if (player->getDexterity() < chestItem->getRequiredDexterity())
            return false;

        if (player->getStrength() < chestItem->getRequiredStrength())
            return false;

        return true;
    }
    return false;
}

void Dialog::leftButtonVerify()
{
    if (canEquipItem())
    {
        ui->equipLeftHand->show();
    }
    else
        ui->equipLeftHand->hide();
}

void Dialog::rightButtonVerify()
{
    if (canEquipItem())
    {
        ui->equipRightHand->show();
    }
    else
        ui->equipRightHand->hide();
}



void Dialog::paintEvent(QPaintEvent *)
{
    rightButtonVerify();
    leftButtonVerify();
    QPainter painter(this);

    qreal width = 55;
    qreal height = 55;

    QRectF rect(0, 0, width, height);

    OneHandedItem *leftHand             = player->getLeftHand();

    if (leftHand)
    {
        painter.save();
        QString playerLeftWeaponType        = QString::fromStdString(leftHand->type());
        QString leftHandDamage              = QString::number(leftHand->getDamage());
        QString leftHandDefence             = QString::number(leftHand->getDefence());
        QString leftHandRequiredDexterity   = QString::number(leftHand->getRequiredDexterity());
        QString leftHandRequiredStrength    = QString::number(leftHand->getRequiredStrength());

        QString text;
        text           += "Damage: " + leftHandDamage + "\n";
        text           += "Defence: " + leftHandDefence + "\n";
        text           += "Required Dexterity: " + leftHandRequiredDexterity + "\n";
        text           += "Required Strength: " + leftHandRequiredStrength + "\n";

        painter.drawText(QRectF(0, 0, 200, 200), text);

        painter.translate(85, 55);
        QImage imgL(playerLeftWeaponType + QString(".png"));
        painter.drawImage(rect, imgL);
        painter.restore();
    }

    OneHandedItem *rightHand             = player->getRightHand();

    if (rightHand)
    {
        painter.save();
        painter.translate(QPointF(330, 0));
        QString playerRightWeaponType        = QString::fromStdString(rightHand->type());
        QString rightHandDamage              = QString::number(rightHand->getDamage());
        QString rightHandDefence             = QString::number(rightHand->getDefence());
        QString rightHandRequiredDexterity   = QString::number(rightHand->getRequiredDexterity());
        QString rightHandRequiredStrength    = QString::number(rightHand->getRequiredStrength());


        QString text;
        text           += "Damage: " + rightHandDamage + "\n";
        text           += "Defence: " + rightHandDefence + "\n";
        text           += "Required Dexterity: " + rightHandRequiredDexterity + "\n";
        text           += "Required Strength: " + rightHandRequiredStrength + "\n";

        painter.drawText(QRectF(0, 0, 200, 200), text);

        painter.translate(-25, 55);
        QImage imgR(playerRightWeaponType + QString(".png"));
        painter.drawImage(rect, imgR);
        painter.restore();
    }

    OneHandedItem *chestItem = (OneHandedItem *)chest->getItem();
    if (chestItem)
    {
        painter.save();
        painter.translate(150, 155);
        QString playerLeftWeaponType        = QString::fromStdString(chestItem->type());
        QString Damage              = QString::number(chestItem->getDamage());
        QString Defence             = QString::number(chestItem->getDefence());
        QString RequiredDexterity   = QString::number(chestItem->getRequiredDexterity());
        QString RequiredStrength    = QString::number(chestItem->getRequiredStrength());

        QString text;
        text           += "Damage: " + Damage + "\n";
        text           += "Defence: " + Defence + "\n";
        text           += "Required Dexterity: " + RequiredDexterity + "\n";
        text           += "Required Strength: " + RequiredStrength + "\n";

        painter.drawText(QRectF(0, 0, 200, 200), text);

        painter.translate(85, 55);
        QImage imgL(playerLeftWeaponType + QString(".png"));
        painter.drawImage(rect, imgL);
        painter.restore();
    }


}

void Dialog::on_equipRightHand_clicked()
{
    OneHandedItem *chestItem = (OneHandedItem *)chest->getItem();
    chest->setItem(player->getRightHand());
    player->setRightHand(chestItem);
    update();
}

void Dialog::on_equipLeftHand_clicked()
{
    OneHandedItem *chestItem = (OneHandedItem *)chest->getItem();
    chest->setItem(player->getLeftHand());
    player->setLeftHand(chestItem);
    update();
}
