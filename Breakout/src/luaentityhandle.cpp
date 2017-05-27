#include "luaentityhandle.h"
#include <iostream>

LuaEntityHandle(const Entity *entity) {
	this->entity = entity;
}

void LuaEntityHandle::setAnimation(const std::string& animationName) {
    std::cout << animationName << std::endl;
}



