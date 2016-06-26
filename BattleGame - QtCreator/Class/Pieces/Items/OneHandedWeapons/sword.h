#ifndef SWORD_H
#define SWORD_H
#include "Class/Pieces/Items/onehandeditem.h"

class Sword : public OneHandedItem
{
public:
    Sword(float x = -1, float y = -1);
    std::string type();
};

#endif // SWORD_H
