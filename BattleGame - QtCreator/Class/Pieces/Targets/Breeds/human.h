#ifndef HUMAN_H
#define HUMAN_H

#include "Class/Pieces/Targets/breed.h"

class Game;

class Human : public Breed
{
public:
    Human(Game *game, float x, float y);
};

#endif // HUMAN_H
