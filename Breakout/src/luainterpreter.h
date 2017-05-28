#ifndef LUAINTERPRETER_H
#define LUAINTERPRETER_H

#include "inc/sol.hpp"


// Used for lua interpreter running on cmd
void* lua_interpreter(void *args);

class LuaInterpreter
{
private:
    static sol::state lua;


public:
    LuaInterpreter();
};

#endif // LUAINTERPRETER_H
