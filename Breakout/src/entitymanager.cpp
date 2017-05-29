#include "entitymanager.h"
#include <iostream>


EntityManager* EntityManager::entityManager = nullptr;


EntityManager *EntityManager::getEntityManager()
{
    std::cout << "LOL\n";
    return entityManager;
}

EntityManager::EntityManager(sol::state &lua) : idCounter(0), lua(lua)
{

}

Entity &EntityManager::create()
{
    auto id = idCounter;
    ++idCounter;
    auto inserted = entities.emplace(id, std::make_unique<Entity>(id));
    auto it = inserted.first; // iterator to created id/Entity pair
    auto& e = *it->second; // created entity
    lua["createHandle"](e);
    return e;

}

void EntityManager::remove(int id)
{
    lua["onEntityRemoved"](id);
    entities.erase(id);
}

void EntityManager::init(sol::state &lua)
{
    entityManager = new EntityManager(lua);
}

