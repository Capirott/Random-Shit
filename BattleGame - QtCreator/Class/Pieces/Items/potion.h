#ifndef POTION_H
#define POTION_H

#include "Class/Pieces/item.h"

class Potion : public Item
{
public:
    Potion(float x = -1, float y = -1);
    std::string type();
};

#endif // POTION_H
