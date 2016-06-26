#include "rock.h"
#include "Class/game.h"
#include "Class/Pieces/Items/onehandeditem.h"
#include "Class/Pieces/chest.h"



Rock::Rock(Game *game, float x, float y)
    :Target(x, y)
{
    this->game = game;
}

void Rock::beingHit(OneHandedItem *item)
{
    if (item->getDamage())
    {
        delete this;
        game->board[x][y] = 0;
    }
}

Rock* Rock::newRock(Game *game, float x, float y)
{
    return new Rock(game, x, y);
}

string Rock::type()
{
    return "Rock";
}
