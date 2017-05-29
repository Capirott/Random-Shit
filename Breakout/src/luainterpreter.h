#ifndef LUAINTERPRETER_H
#define LUAINTERPRETER_H

#include "inc/sol.hpp"


// Used for lua interpreter running on cmd
void* lua_interpreter(void *args);

class LuaInterpreter
{
public:
    static sol::state lua;
    static void load_interpreter();
    LuaInterpreter();
};

#endif // LUAINTERPRETER_H
