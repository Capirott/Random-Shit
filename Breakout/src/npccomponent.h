#ifndef NPCCOMPONENT_H
#define NPCCOMPONENT_H

#include <string>
#include "component.h"
 
class NpcComponent : public Component {
public:
   
    NpcComponent(luabridge::LuaRef& componentTable);
 
    void setPhrase(const std::string& phrase) {
        this->phrase = phrase;
    }
 
    std::string getPhrase() const {
        return phrase;
    }


private:
    std::string phrase;
};

#endif
