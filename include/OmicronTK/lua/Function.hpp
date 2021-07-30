#pragma once

#include "OmicronTK/lua/global.h"
#include "OmicronTK/lua/Value.hpp"

namespace OmicronTK {
namespace lua {

class Lua;
class Object;
class OTKLUA_EXPORT Function
{
public:
    Function(Lua *lua, Object *object, int ref);
    ~Function();

    void call(const ValueVec &values = {});

private:
    int m_ref;
    Lua *m_lua;
    Object *m_object;
};

}
}
