#include "bomb.h"
#include <cstdlib>

#define BOMB_DAMAGE rand () % 11 + 5

Bomb::Bomb(float x, float y)
    :Item(x, y)
{
    this->damage = BOMB_DAMAGE;
}

WORD Bomb::getDamage()
{
    return damage;
}

std::string Bomb::type()
{
    return "Bomb";
}

#undef BOMB_DAMAGE
