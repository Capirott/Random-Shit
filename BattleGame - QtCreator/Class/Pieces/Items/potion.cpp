#include "potion.h"

Potion::Potion(float x, float y)
    :Item(x, y)
{

}

std::string Potion::type()
{
    return "Potion";
}
