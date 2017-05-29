#include "luainterpreter.h"
#include "entitymanager.h"
#include "entity.h"
#include "opengl.h"


sol::state LuaInterpreter::lua = sol::state();


void* lua_interpreter(void *args)
{
    sol::state &lua = *(sol::state *)args;

    EntityManager &entityManager = *EntityManager::getEntityManager();

    lua.open_libraries();

    lua.new_usertype<Entity>("Entity",
        sol::constructors<Entity(int)>(),
        "id", sol::readonly_property(&Entity::getId),
        "x", sol::property(&Entity::getX, &Entity::setX),
        "y", sol::property(&Entity::getY, &Entity::setY),
        "z", sol::property(&Entity::getZ, &Entity::setZ),
        "position", sol::property(&Entity::getPosition, &Entity::setPosition)
    );

    lua.new_usertype<EntityManager>("EntityManager",
        "create", &EntityManager::create,
        "remove", &EntityManager::remove
    );

    lua["EntityManager"] = std::ref(entityManager);

    lua.do_file(PROJECT_DIR + "script/entity.lua");



    std::cout << "Starting lua interpreter!\n";
    std::string line;
    while (true)
    {
        try
        {
            std::cout << ">> ";
            std::getline(std::cin, line);
            lua.script(line);
        } catch (sol::error er)
        {
            std::cout << er.what() << std::endl;
        }
    }

    return nullptr;
}
