#pragma once

#include "OmicronTK/lua/Value.hpp"

namespace OmicronTK {
namespace lua {

class Lua;
class Object;
class Function
{
public:
    Function(Lua *lua, Object *object, int ref);
    ~Function();

    void call(const ValueVector &values = {});

private:
    int m_ref;
    Lua *m_lua;
    Object *m_object;
};

}
}
