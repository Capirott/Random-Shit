#ifndef LUAENTITYHANDLE_H
#define LUAENTITYHANDLE_H

#include "entity.h"

class LuaEntityHandle {

private:
	Entity* entity;

public:
	void setAnimation(const std::string& name);
	LuaEntityHandle(const Entity *entity);    
}

#endif
