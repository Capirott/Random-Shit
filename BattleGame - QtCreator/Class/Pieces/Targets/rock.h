#ifndef ROCK_H
#define ROCK_H

#include "Class/Pieces/target.h"

class Game;

class Rock : public Target
{
private:
    Game *game;
    Rock(Game *game, float x = -1, float y = -1);
public:
    void beingHit(OneHandedItem *);
    static Rock* newRock(Game *game, float x = -1, float y = -1);
    string type();
};

#endif // ROCK_H
