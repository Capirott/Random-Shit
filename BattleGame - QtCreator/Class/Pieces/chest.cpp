#include "chest.h"
#include <cstdlib>

#include "Class/Pieces/Items/bomb.h"
#include "Class/Pieces/Items/potion.h"
#include "Class/Pieces/Items/OneHandedWeapons/axe.h"
#include "Class/Pieces/Items/OneHandedWeapons/bow.h"
#include "Class/Pieces/Items/OneHandedWeapons/shield.h"
#include "Class/Pieces/Items/OneHandedWeapons/sword.h"

enum Chest_Item
{
    BOMB,
    POTION,
    AXE,
    BOW,
    SHIELD,
    SWORD
};

Chest::Chest(float x, float y)
    :Piece(x, y)
{
    switch(rand() % 6)
    {
    case BOMB:
        item = new Bomb();
        break;
    case POTION:
        item = new Potion();
        break;
    case AXE:
        item = new Axe();
        break;
    case BOW:
        item = new Bow();
        break;
    case SHIELD:
        item = new Shield();
        break;
    case SWORD:
        item = new Sword();
        break;
    default:
        throw "Error";
        break;
    }
}

string Chest::type()
{
    return "Chest";
}

string Chest::getItemType()
{
    if (!item)
        return "";
    return item->type();
}

void Chest::setItem(Item *item)
{
    this->item = item;
}

Item* Chest::getItem()
{
    return item;
}
