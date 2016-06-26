#ifndef BARBARIAN_H
#define BARBARIAN_H

#include "Class/Pieces/Targets/Breeds/human.h"

class Barbarian : public Human
{
public:
    Barbarian(Game *game, float x = -1, float y = -1);
    string type();
};

#endif // BARBARIAN_H
