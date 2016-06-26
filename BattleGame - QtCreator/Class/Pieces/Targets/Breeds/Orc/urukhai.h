#ifndef URUKHAI_H
#define URUKHAI_H
#include "Class/Pieces/Targets/Breeds/orc.h"

class UrukHai : public Orc
{
public:
    UrukHai(Game *game, float x = -1, float y = -1);
    string type();
};

#endif // URUKHAI_H
