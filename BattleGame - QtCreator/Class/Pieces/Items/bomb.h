#ifndef BOMB_H
#define BOMB_H
#include "Class/Pieces/item.h"
#include <string>

typedef unsigned short WORD;

class Bomb : public Item
{
private:
    WORD damage;
public:
    Bomb(float x = -1, float y = -1);
    WORD getDamage();
    std::string type();
};

#endif // BOMB_H
