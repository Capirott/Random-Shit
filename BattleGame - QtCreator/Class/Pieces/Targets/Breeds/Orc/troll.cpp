#include "troll.h"
#include "Class/Pieces/Targets/Breeds/orc.h"
#include "Class/Pieces/Items/OneHandedWeapons/Axe.h"

#define AXE_DAMAGE                10
#define AXE_DEFENCE               3
#define AXE_REQUIRED_STRENGTH     70
#define AXE_REQUIRED_DEXTERITY    15

#define MAX_HP 80
#define STRENGTH 80
#define DEXTERITY 20

Troll::Troll(Game *game, float x, float y)
    : Orc(game, x, y)
{
    leftHand = new Axe(0, 0);
    leftHand->setDamage(AXE_DAMAGE);
    leftHand->setDefence(AXE_DEFENCE);
    leftHand->setRequiredStrength(AXE_REQUIRED_STRENGTH);
    leftHand->setRequiredDexterity(AXE_REQUIRED_DEXTERITY);
    hp              = MAX_HP;
    hpMax           = MAX_HP;
    strength        = STRENGTH;
    dexterity       = DEXTERITY;
}

string Troll::type()
{
    return "Troll";
}

#undef AXE_DAMAGE
#undef AXE_DEFENCE
#undef AXE_REQUIRED_STRENGTH
#undef AXE_REQUIRED_DEXTERITY

#undef MAX_HP
#undef STRENGTH
#undef DEXTERITY



