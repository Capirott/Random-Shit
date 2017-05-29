#ifndef ENTITY_H
#define ENTITY_H

#include "inc/sol.hpp"
#include "glm/glm.hpp"
#include <typeindex>
#include <map>

#include "component.h"

class Entity {

private:
    int id;

    float x;
    float y;
    float z;

    std::map<std::type_index, Component *> component;

    std::string type;

public:
    explicit Entity(int id);
    ~Entity();
    int getId() const { return id; }

    float getX() const;
    void setX(float value);
    float getY() const;
    void setY(float value);
    float getZ() const;
    void setZ(float value);
    glm::vec3 getvec3();

    std::vector<float> getPosition();
    void setPosition(const sol::table &position);
    std::string getType() const;
    void setType(const std::string &value);

    void addComponent(std::type_index type, Component *c);

    template <typename T>
    T* get() {
        auto it = component.find(std::type_index(typeid(T)));
        if (it != component.end()) {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }

};

#endif
