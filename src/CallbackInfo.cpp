#include "OmicronTK/lua/CallbackInfo.hpp"

#include <lua.hpp>

namespace OmicronTK {
namespace lua {

CallbackInfo::CallbackInfo(lua_State *L)
    : m_state(L)
{

}

int CallbackInfo::length()
{
    return lua_gettop(m_state);
}

}
}
