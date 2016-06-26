#include "orc.h"
#include "Class/Pieces/Items/potion.h"

#define MAX_POTIONS 2

Orc::Orc(Game *game, float x, float y)
    : Breed(game, x, y)
{
    Breed::potionsMax = MAX_POTIONS;
}

#undef MAX_POTIONS
