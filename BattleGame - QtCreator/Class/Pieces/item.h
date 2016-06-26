#ifndef ITEM_H
#define ITEM_H

#include "Class/piece.h"


class Item : public Piece
{
public:
    Item(float x = -1, float y = -1);
    virtual std::string type() = 0;
};

#endif // ITEM_H
