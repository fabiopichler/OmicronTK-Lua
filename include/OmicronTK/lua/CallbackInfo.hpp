#pragma once

#include "OmicronTK/lua/defines.hpp"

namespace OmicronTK {
namespace lua {

class CallbackInfo
{
public:
    CallbackInfo(lua_State *L);

    inline lua_State *state() { return m_state; }

    int length();

private:
    lua_State *m_state;
};

using LuaCppFunction = int (*)(CallbackInfo info);

}
}
