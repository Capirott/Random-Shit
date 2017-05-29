#ifndef LIFECOMPONENT_H
#define LIFECOMPONENT_H

#include "component.h"


class LifeComponent : public Component
{
private:
    int live;
public:
    LifeComponent();

    int getLive() const;
    void setLive(int value);
};

#endif // LIFECOMPONENT_H
