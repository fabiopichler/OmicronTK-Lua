#pragma once

#include <string>

#include "OmicronTK/lua/global.h"

namespace OmicronTK {
namespace lua {

class Lua;
class Function;
class OTKLUA_EXPORT Object
{
public:
    Object(Lua *lua, int ref);
    ~Object();

    inline int getRef() const { return m_ref; }

    Function *getFunction(const std::string &name);

private:
    int m_ref;
    Lua *m_lua;
};

}
}
