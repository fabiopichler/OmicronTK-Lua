#pragma once

#include "OmicronTK/lua/Value.hpp"

namespace OmicronTK {
namespace lua {

void LuaRegVector_forEach(lua_State *L, const RegVector &values);

void pcall(lua_State *state, const std::string &name, const ValueVector &values, size_t returnsSize);
void pcallTable(lua_State *state, bool isObject, const std::string &table, const std::string &field,
                const ValueVector &values, size_t returnsSize);
ValueVector pcallReturn(lua_State *state, const std::vector<Value::Type> &returns);

Value toValue(lua_State *state, Value::Type type, uint32_t idx);

void pushValue(lua_State *state, const Value &value);

}
}
