#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>

class Game;

class RenderArea : public QWidget
{
private:
    Game *game;
    Q_OBJECT
public:
    RenderArea(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

    bool event(QEvent *event);
    void setGame(Game *game);
};

#endif // RENDERAREA_H
