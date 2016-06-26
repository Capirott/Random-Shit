#include "bow.h"
#include "Class/Pieces/Items/onehandeditem.h"
#include <cstdlib>

#define BOW_DAMAGE                rand() % 6 + 5
#define BOW_DEFENCE               0
#define BOW_REQUIRED_STRENGTH     rand() % 11 + 10
#define BOW_REQUIRED_DEXTERITY    rand() % 61 + 20

Bow::Bow(float x, float y)
    : OneHandedItem(x, y, BOW_DAMAGE, BOW_DEFENCE, BOW_REQUIRED_STRENGTH, BOW_REQUIRED_DEXTERITY)
{
}

std::string Bow::type()
{
    return "Bow";
}


#undef BOW_DAMAGE
#undef BOW_DEFENCE
#undef BOW_REQUIRED_STRENGTH
#undef BOW_REQUIRED_DEXTERITY
