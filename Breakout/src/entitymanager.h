#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "entity.h"

class EntityManager {

private:
    std::unordered_map<int, std::unique_ptr<Entity>> entities;
    int idCounter;
    sol::state &lua;
    static EntityManager *entityManager;



    EntityManager(sol::state &lua);
public:

    Entity& create();

    void remove(int id);

    static void init(sol::state &lua);

    static EntityManager *getEntityManager();
};
#endif // ENTITYMANAGER_H
