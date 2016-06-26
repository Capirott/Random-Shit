#include "axe.h"
#include "Class/Pieces/Items/onehandeditem.h"
#include <cstdlib>

#define AXE_DAMAGE              rand() % 11 + 10
#define AXE_DEFENCE             rand() % 6 + 5
#define AXE_REQUIRED_STRENGTH   rand() % 71 + 10
#define AXE_REQUIRED_DEXTERITY  rand() % 21 + 5


Axe::Axe(float x, float y)
    : OneHandedItem(x, y, AXE_DAMAGE, AXE_DEFENCE, AXE_REQUIRED_STRENGTH, AXE_REQUIRED_DEXTERITY)
{
}

std::string Axe::type()
{
    return "Axe";
}

#undef AXE_DAMAGE
#undef AXE_DEFENCE
#undef AXE_REQUIRED_STRENGTH
#undef AXE_REQUIRED_DEXTERITY
