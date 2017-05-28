#include "luainterpreter.h"
#include "entity.h"
#include "opengl.h"


LuaInterpreter::LuaInterpreter()
{

}



void* lua_interpreter(void *args)
{
    sol::state lua;
    lua.open_libraries();

    lua.new_usertype<Entity>("Entity",
        "getName", &Entity::getName,
        "setName", &Entity::setName,
        "getId", &Entity::getId
    );


    lua.do_file(PROJECT_DIR + "script/entity.lua");


    EntityManager entityManager(lua);
    auto& entity = entityManager.createEntity();

    lua["test"](entity);

    std::cout << "Testing bad reference" << std::endl;
    lua["testBadReference"](entity);

    std::string line;
    while (true) {
        try {
            std::getline(std::cin, line);
            lua.script(line);
        } catch (sol::error er) {
            std::cout << er.what() << std::endl;
        }
    }

    return nullptr;
}
