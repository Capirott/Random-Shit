#ifndef ONEHANDEDITEM_H
#define ONEHANDEDITEM_H
#include "Class/Pieces/item.h"

class OneHandedItem : public Item
{
protected:
    float damage;
    float defence;
    float requiredStrength;
    float requiredDexterity;
public:
    void setDamage(float damage);
    void setDefence(float defence);
    void setRequiredStrength(float requiredStrength);
    void setRequiredDexterity(float requiredDexterity);
    float getDamage();
    float getDefence();
    float getRequiredStrength();
    float getRequiredDexterity();
    OneHandedItem(float x, float y, float damage, float defence, float requiredStrength, float requiredDexterity);
    virtual std::string type() = 0;
};

#endif // ONEHANDEDITEM_H
