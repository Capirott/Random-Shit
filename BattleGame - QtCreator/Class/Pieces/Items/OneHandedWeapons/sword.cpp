#include "sword.h"
#include "Class/Pieces/Items/onehandeditem.h"
#include <cstdlib>

#define SWORD_DAMAGE                rand() % 11 + 5
#define SWORD_DEFENCE               rand() % 6
#define SWORD_REQUIRED_STRENGTH     rand() % 31 + 10
#define SWORD_REQUIRED_DEXTERITY    rand() % 26 + 15

Sword::Sword(float x, float y)
    : OneHandedItem(x, y, SWORD_DAMAGE, SWORD_DEFENCE, SWORD_REQUIRED_STRENGTH, SWORD_REQUIRED_DEXTERITY)
{
}

std::string Sword::type()
{
    return "Sword";
}

#undef SWORD_DAMAGE
#undef SWORD_DEFENCE
#undef SWORD_REQUIRED_STRENGTH
#undef SWORD_REQUIRED_DEXTERITY
