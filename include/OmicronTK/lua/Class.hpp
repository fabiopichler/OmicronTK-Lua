#pragma once

#include "OmicronTK/lua/Value.hpp"

namespace OmicronTK {
namespace lua {

class Lua;
class Object;
class Class
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
