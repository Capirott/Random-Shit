#include "barbarian.h"
#include "Class/Pieces/Targets/Breeds/human.h"
#include "Class/Pieces/Items/OneHandedWeapons/sword.h"

#define SWORD_DAMAGE                7
#define SWORD_DEFENCE               3
#define SWORD_REQUIRED_STRENGTH     20
#define SWORD_REQUIRED_DEXTERITY    50

#define MAX_HP 30
#define STRENGTH 60
#define DEXTERITY 60

Barbarian::Barbarian(Game *game, float x, float y)
    : Human(game, x, y)
{
    leftHand = new Sword(0, 0);
    leftHand->setDamage(SWORD_DAMAGE);
    leftHand->setDefence(SWORD_DEFENCE);
    leftHand->setRequiredStrength(SWORD_REQUIRED_STRENGTH);
    leftHand->setRequiredDexterity(SWORD_REQUIRED_DEXTERITY);
    hp              = MAX_HP;
    hpMax           = MAX_HP;
    strength        = STRENGTH;
    dexterity       = DEXTERITY;
}

string Barbarian::type()
{
    return "Barbarian";
}

#undef SWORD_DAMAGE
#undef SWORD_DEFENCE
#undef SWORD_REQUIRED_STRENGTH
#undef SWORD_REQUIRED_DEXTERITY

#undef MAX_HP
#undef STRENGTH
#undef DEXTERITY
