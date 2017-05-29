#include "inc/sol.hpp"
#include "entity.h"
#include "opengl.h"
#include <string>
#include <iostream>

float Entity::getX() const
{
    return x;
}

void Entity::setX(float value)
{
    x = value;
}

float Entity::getY() const
{
    return y;
}

void Entity::setY(float value)
{
    y = value;
}

float Entity::getZ() const
{
    return z;
}

void Entity::setZ(float value)
{
    z = value;
}

glm::vec3 Entity::getvec3()
{
    return glm::vec3(x, y, z);
}

std::string Entity::getType() const
{
    return type;
}

void Entity::setType(const std::string &value)
{
    type = value;
}

void Entity::addComponent(std::type_index type, Component *c)
{
    component[type] = c;
}

Entity::Entity(int id)
{
    this->id = id;
    x = y = z = 0.0f;
}

Entity::~Entity()
{
    for (auto& c : component) {
        delete c.second;
    }
}

std::vector<float> Entity::getPosition()
{
    std::vector<float> ref{x, y, z};
    return ref;
}

void Entity::setPosition(const sol::table &position)
{
    this->x = position[1];
    this->y = position[2];
    this->z = position[3];
}
