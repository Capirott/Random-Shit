#ifndef TROLL_H
#define TROLL_H
#include "Class/Pieces/Targets/Breeds/orc.h"

class Troll : public Orc
{
public:
    Troll(Game *game, float x = -1, float y = -1);
    string type();
};

#endif // TROLL_H
