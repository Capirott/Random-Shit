#ifndef AXE_H
#define AXE_H
#include "Class/Pieces/Items/onehandeditem.h"

class Axe : public OneHandedItem
{
public:
    Axe(float x = -1, float y = -1);
    std::string type();
};

#endif // AXE_H
