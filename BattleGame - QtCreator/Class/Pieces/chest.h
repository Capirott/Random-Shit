#ifndef CHEST_H
#define CHEST_H

#include "Class/piece.h"

class Item;

class Chest : public Piece
{
private:
    Item *item;
public:
    Chest(float x, float y);
    string type();
    string getItemType();

    void setItem(Item *item);
    Item *getItem();
};

#endif // CHEST_H
