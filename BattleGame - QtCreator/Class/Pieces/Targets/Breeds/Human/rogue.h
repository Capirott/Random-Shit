#ifndef ROGUE_H
#define ROGUE_H

#include "Class/Pieces/Targets/Breeds/human.h"

class Game;

class Rogue : public Human
{
public:
    Rogue(Game *game, float x, float y);
    string type();
};

#endif // ROGUE_H
