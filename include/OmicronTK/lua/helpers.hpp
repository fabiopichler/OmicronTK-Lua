#pragma once

#include "OmicronTK/lua/LuaValue.hpp"

namespace OmicronTK {
namespace lua {

void LuaRegVector_forEach(lua_State *L, const LuaRegVector &values);

void pcall(lua_State *state, const std::string &name, const LuaValueVector &values, size_t returnsSize);
void pcallTable(lua_State *state, bool isObject, const std::string &table, const std::string &field,
                const LuaValueVector &values, size_t returnsSize);
LuaValueVector pcallReturn(lua_State *state, const std::vector<LuaValue::Type> &returns);

LuaValue toLuaValue(lua_State *state, LuaValue::Type type, uint32_t idx);

void pushLuaValue(lua_State *state, const LuaValue &value);

}
}
