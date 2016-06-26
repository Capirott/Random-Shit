#ifndef SHIELD_H
#define SHIELD_H
#include "Class/Pieces/Items/onehandeditem.h"

class Shield : public OneHandedItem
{
public:
    Shield(float x = -1, float y = -1);
    string type();
};

#endif // SHIELD_H
