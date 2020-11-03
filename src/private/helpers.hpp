#pragma once

#include "OmicronTK/lua/LuaValue.hpp"

namespace OmicronTK {
namespace lua {

void LuaRegVector_forEach(lua_State *L, const LuaRegVector &values);

LuaValue toLuaValue(lua_State *state, LuaValueType type, uint32_t idx);

void pushLuaValue(lua_State *state, const LuaValue &value);

}
}
