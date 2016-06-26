#ifndef TARGET_H
#define TARGET_H

#include "Class/piece.h"

class OneHandedItem;

class Target : public Piece
{
public:    
    Target(float, float);
    virtual void beingHit(OneHandedItem *) = 0;
};

#endif // TARGET_H
