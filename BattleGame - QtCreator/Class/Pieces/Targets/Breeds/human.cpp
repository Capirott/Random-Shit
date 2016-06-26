#include "human.h"
#include "Class/Pieces/Items/potion.h"

#define MAX_POTIONS 3

Human::Human(Game *game, float x, float y)
    : Breed(game, x, y)
{
    Breed::potionsMax = MAX_POTIONS;
}
