#include "onehandeditem.h"

OneHandedItem::OneHandedItem(float x, float y, float damage, float defence, float requiredStrength, float requiredDexterity)
    : Item(x, y)
{
    this->x = x;
    this->y = y;
    this->damage = damage;
    this->defence = defence;
    this->requiredStrength = requiredStrength;
    this->requiredDexterity = requiredDexterity;
}

void OneHandedItem::setDamage(float damage)
{
    this->damage = damage;
}

float OneHandedItem::getDamage()
{
    return damage;
}

void OneHandedItem::setDefence(float defence)
{
    this->defence = defence;
}

float OneHandedItem::getDefence()
{
    return defence;
}

void OneHandedItem::setRequiredStrength(float requiredStrength)
{
    this->requiredStrength = requiredStrength;
}

float OneHandedItem::getRequiredStrength()
{
    return requiredStrength;
}

void OneHandedItem::setRequiredDexterity(float requiredDexterity)
{
    this->requiredDexterity = requiredDexterity;
}

float OneHandedItem::getRequiredDexterity()
{
    return requiredDexterity;
}
