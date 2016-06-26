#include "renderareastatus.h"
#include "Class/game.h"
#include <QPainter>
#include "Class/Pieces/Targets/breed.h"
#include <QDesktopWidget>
#include <QApplication>

RenderAreaStatus::RenderAreaStatus(Game *game, QWidget *parent)
    : QWidget(parent)
{
    this->game = game;
    setMinimumSize(QApplication::desktop()->geometry().width() * 0.99, QApplication::desktop()->geometry().height() * 0.13);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMouseTracking(true);
}

void RenderAreaStatus::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(QColor("black")));
    painter.setFont(QFont("Arial", 20));
    painter.save();
    Breed *player = game->player[0];
    if (player->isAlive())
    {
        QString text;
        text += QString::fromStdString(player->getName()
                                       + "(" + player->type() + ")\nHp: ")
                + QString::number(player->getHp())
                + "/" + QString::number(player->getMaxHp())
                + "\nPotions: "  + QString::number(player->getPotions())
                + "/" + QString::number(player->getPotionsMax());

        painter.drawText(QRectF(0, 0, 250, 250), text);

        text = "Dexterity: " + QString::number(player->getDexterity()) + "\n"
                + "Strength: " + QString::number(player->getStrength()) + "\n";

        painter.setFont(QFont("Arial", 10));
        painter.drawText(QRectF(width() * 0.10 + 100, 0, 250, 250), text);

    }
    else
    {
        QString text;
        text += QString::fromStdString(player->getName()
                                       + "(" + player->type() + ")\nHp: (DEAD)")
                + "\nPotions: "  + QString::number(player->getPotions())
                + "/" + QString::number(player->getPotionsMax());

        painter.drawText(QRectF(0, 0, 250, 250), text);

    }
    painter.restore();
    player = game->player[1];
    painter.translate(width() * 0.75, 0);
    if (player->isAlive())
    {
        QString text;
        text += QString::fromStdString(player->getName()
                                       + "(" + player->type() + ")\nHp: ")
                + QString::number(player->getHp())
                + "/" + QString::number(player->getMaxHp())
                + "\nPotions: "  + QString::number(player->getPotions())
                + "/" + QString::number(player->getPotionsMax());
        painter.drawText(QRectF(0, 0, 500, 500), text);


        text = "Dexterity: " + QString::number(player->getDexterity()) + "\n"
                + "Strength: " + QString::number(player->getStrength()) + "\n";

        painter.setFont(QFont("Arial", 10));
        painter.drawText(QRectF(- width() * 0.075, 0, 250, 250), text);

    }
    else
    {
        QString text;
        text += QString::fromStdString(player->getName()
                                       + "(" + player->type() + ")\nHp: (DEAD)")
                + "\nPotions: "  + QString::number(player->getPotions())
                + "/" + QString::number(player->getPotionsMax());

        painter.drawText(QRectF(0, 0, 500, 500), text);
    }
}
