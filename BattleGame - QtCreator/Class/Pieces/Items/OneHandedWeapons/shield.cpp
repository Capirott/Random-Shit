#include "shield.h"
#include <cstdlib>

#define SHIELD_DAMAGE                0
#define SHIELD_DEFENCE               rand() % 11 + 5
#define SHIELD_REQUIRED_STRENGTH     rand() % 31 + 10
#define SHIELD_REQUIRED_DEXTERITY    rand() % 36 + 15

Shield::Shield(float x, float y)
    : OneHandedItem(x, y, SHIELD_DAMAGE, SHIELD_DEFENCE, SHIELD_REQUIRED_STRENGTH, SHIELD_REQUIRED_DEXTERITY)
{
}

std::string Shield::type()
{
    return "Shield";
}

#undef SHIELD_DAMAGE
#undef SHIELD_DEFENCE
#undef SHIELD_REQUIRED_STRENGTH
#undef SHIELD_REQUIRED_DEXTERITY
