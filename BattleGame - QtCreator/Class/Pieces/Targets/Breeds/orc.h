#ifndef ORC_H
#define ORC_H
#include "Class/Pieces/Targets/breed.h"

class Game;

class Orc : public Breed
{
public:
    Orc(Game *game, float x, float y);
};

#endif // ORC_H
