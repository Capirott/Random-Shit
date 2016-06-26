#include "renderarea.h"

#include <QPen>
#include <QPainter>
#include "Class/game.h"
#include <typeinfo>
#include "Class/Pieces/Targets/rock.h"
#include <iostream>
#include "Class/Pieces/Targets/breed.h"
#include <QToolTip>
#include <QKeyEvent>
#include <QApplication>
#include "Class/Pieces/chest.h"
#include <QApplication>
#include <QDesktopWidget>

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    game = 0;
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setMouseTracking(true);
    setMinimumSize(QApplication::desktop()->geometry().width() * 0.99, QApplication::desktop()->geometry().height() * 0.85);
}

void RenderArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

       if (game)
       {
           DWORD x = game->getX();
           DWORD y = game->getY();

           QRectF rect(0, 0, width() / y, height() / x);
           painter.setRenderHint(QPainter::Antialiasing);

           painter.setPen(QColor("#102372"));
           for (DWORD i = 0; i < y; ++i)
           {
               for (DWORD j = 0; j < x; ++j)
               {
                   painter.save();
                   painter.translate(QPointF(i * (width() / y), j * (height() / x)));
//                   painter.drawRect(QRect(0, 0, width() / y, height() / x));
                   Piece *tmp = game->board[j][i];
                   if (tmp)
                   {
                       QString type = QString::fromStdString(tmp->type());
                       if (type == "Rock" || type == "Chest")
                       {
                           QImage img(QString(type + QString(".png")));
                           painter.drawImage(rect, img);
                       }
                   }
                   painter.restore();
               }
           }
           for (DWORD i = 0; i < 2; ++i)
           {
               painter.save();

               DWORD x = game->getX();
               DWORD y = game->getY();

               painter.translate(QPointF(game->player[i]->getY() * (width() / y), game->player[i]->getX() * (height() / x)));

               QString type = QString::fromStdString(game->player[i]->type());

               if (game->player[i]->isAlive())
               {
                   QImage img(QString(type + QString(".png")));
                   painter.drawImage(rect, img);

                   QRectF rect(0, 0, width() / y / 3, height() / x / 3);

                   QString playerLeftWeapon = QString::fromStdString(game->player[i]->getLeftHandType());
                   QImage imgL(playerLeftWeapon + QString(".png"));
                   painter.drawImage(rect, imgL);

                   QString playerRightWeapon = QString::fromStdString(game->player[i]->getRightHandType());
                   QImage imgR(playerRightWeapon + QString(".png"));
                   painter.drawImage(rect.translated(QPointF(width() / y * 0.7, 0)), imgR);
                   if (game->player[i]->isDefending())
                   {
                       painter.drawRect(QRect(0, 0, width() / y, height() / x));
                   }
              }
               else
               {
                   painter.setOpacity(0.5);
                   QImage img(QString(type + QString(".png")));
                   painter.drawImage(rect, img);
               }
               painter.restore();
           }
       }
       else
       {
           qreal real = width() * height() * 0.0001;
           QPen pen(QColor("red"));
           painter.setPen(pen);
           painter.setFont(QFont("Arial", real));
           painter.drawText(QRectF(width() / 2 - 5 *real, height() / 2 - real, width(), height()), QString("Start a new game!"));
       }
}

void RenderArea::setGame(Game *game)
{
    this->game = game;
}

bool RenderArea::event(QEvent *event)
{

    if (event->type() == QEvent::ToolTip) {

        DWORD x = game->getX();
        DWORD y = game->getY();
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);

        QRectF rect(0, 0, width() / y, height() / x);

        Breed *player = 0;
        string toolTip;
        for (int i = 0; i < 2; ++i)
        {
            if (rect.contains(helpEvent->pos() - QPointF(game->player[i]->getY() * (width() / y),
                                                         game->player[i]->getX() * (height() / x)))
                    )
                player = game->player[i];
        }
        if (player)
        {
            toolTip += player->getName() + "(" + player->getDirection() + ")\n";
        }
        DWORD i = helpEvent->y() / (height() / x);
        DWORD j = helpEvent->x() / (width() / y);
        if (i < game->getX() && j < game->getY() && game->board[i][j])
        {
            toolTip += game->board[i][j]->type() + "\n";
            if (game->board[i][j]->type() == "Chest")
            {
                toolTip += "- " + ((Chest *)game->board[i][j])->getItemType() + "\n";
            }
        }
        if (toolTip == "")
        {
            QToolTip::hideText();
            event->ignore();
        }
        else
        {
            *(toolTip.end() - 1) = '\0';
            QToolTip::showText(helpEvent->globalPos(), QString::fromStdString(toolTip));
        }
        return true;
    }
    return QWidget::event(event);
}

