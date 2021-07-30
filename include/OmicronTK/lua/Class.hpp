#pragma once

#include "OmicronTK/lua/global.h"
#include "OmicronTK/lua/Value.hpp"

namespace OmicronTK {
namespace lua {

class Lua;
class Object;
class OTKLUA_EXPORT Class
{
public:
    Class(Lua *lua, int ref);
    ~Class();

    Object *callConstructor(const ValueVec &values = {});

private:
    int m_ref;
    Lua *m_lua;
};

}
}
