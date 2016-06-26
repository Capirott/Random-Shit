#ifndef BOW_H
#define BOW_H
#include "Class/Pieces/Items/onehandeditem.h"

class Bow : public OneHandedItem
{
public:
    Bow(float x = -1, float y = -1);
    std::string type();
};

#endif // BOW_H
