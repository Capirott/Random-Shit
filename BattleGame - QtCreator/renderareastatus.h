#ifndef RENDERAREASTATUS_H
#define RENDERAREASTATUS_H

#include <QWidget>

class Game;

class RenderAreaStatus : public QWidget
{
    Q_OBJECT
private:
    Game *game;
public:
    RenderAreaStatus(Game *game, QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
};

#endif // RENDERAREASTATUS_H
