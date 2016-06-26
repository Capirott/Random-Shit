#include "rogue.h"
#include "Class/Pieces/Items/OneHandedWeapons/bow.h"

#define BOW_DAMAGE                5
#define BOW_DEFENCE               1
#define BOW_REQUIRED_STRENGTH     15
#define BOW_REQUIRED_DEXTERITY    60

#define MAX_HP 30
#define STRENGTH 20
#define DEXTERITY 80

Rogue::Rogue(Game *game, float x, float y)
    : Human(game, x, y)
{
    leftHand = new Bow(0, 0);
    leftHand->setDamage(BOW_DAMAGE);
    leftHand->setDefence(BOW_DEFENCE);
    leftHand->setRequiredStrength(BOW_REQUIRED_STRENGTH);
    leftHand->setRequiredDexterity(BOW_REQUIRED_DEXTERITY);
    hp              = MAX_HP;
    hpMax           = MAX_HP;
    strength        = STRENGTH;
    dexterity       = DEXTERITY;
}

string Rogue::type()
{
    return "Rogue";
}

#undef BOW_DAMAGE
#undef BOW_DEFENCE
#undef BOW_REQUIRED_STRENGTH
#undef BOW_REQUIRED_DEXTERITY

#undef MAX_HP
#undef STRENGTH
#undef DEXTERITY
