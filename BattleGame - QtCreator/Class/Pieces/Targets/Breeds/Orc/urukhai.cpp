#include "urukhai.h"
#include "Class/Pieces/Targets/Breeds/orc.h"
#include "Class/Pieces/Items/OneHandedWeapons/sword.h"

#define SWORD_DAMAGE                8
#define SWORD_DEFENCE               2
#define SWORD_REQUIRED_STRENGTH     40
#define SWORD_REQUIRED_DEXTERITY    40

#define MAX_HP 40
#define STRENGTH 60
#define DEXTERITY 40

UrukHai::UrukHai(Game *game, float x, float y)
    : Orc(game, x, y)
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

string UrukHai::type()
{
    return "UrukHai";
}

#undef SWORD_DAMAGE
#undef SWORD_DEFENCE
#undef SWORD_REQUIRED_STRENGTH
#undef SWORD_REQUIRED_DEXTERITY

#undef MAX_HP
#undef STRENGTH
#undef DEXTERITY
