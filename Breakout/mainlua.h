#include <LuaBridge.h>
#include <iostream>
#include <typeindex>
#include "entity.h"
#include "component.h"
#include "npccomponent.h"
#include "graphicscomponent.h"
#include "luahelperfunctions.h"


extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#define DST_SRC_FOLDER std::string("script/")
 
using namespace luabridge;
 

template <typename T>
void addComponent(Entity* e, luabridge::LuaRef& componentTable) {
    e->addComponent(std::type_index(typeid(T)), new T(componentTable));
}

Entity* loadEntity(lua_State* L, const std::string& type) {
    using namespace luabridge;
    Entity *e = new Entity();
    e->setType(type);
    std::vector<std::string> vKeys = luah::getTableKeys(L, type);
    LuaRef entityTable = getGlobal(L, type.c_str());
    for (std::string &componentName : vKeys) {
        if (componentName == "GraphicsComponent") {
            LuaRef gcTable = entityTable["GraphicsComponent"];
            addComponent<GraphicsComponent>(e, gcTable);
        } else if (componentName == "NpcComponent") {
            LuaRef npccTable = entityTable["NpcComponent"];
            addComponent<NpcComponent>(e, npccTable);
        }
 
        std::cout << "Added " << componentName << " to " << type << std::endl;
    }
    return e;
}

void* lua_interpreter(void *arg){
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	 
	luah::loadScript(L, DST_SRC_FOLDER + "ghost.lua");
	luah::loadGetKeysFunction(L);
	 
	auto e = loadEntity(L, "ghost");
	auto npcc = e->get<NpcComponent>();
	std::cout << e->getType() << " says: " << npcc->getPhrase() << std::endl;
 
	lua_close(L);
	return nullptr; 
}
