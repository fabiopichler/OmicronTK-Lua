#pragma once

#include "OmicronTK/lua/global.h"
#include "OmicronTK/lua/Value.hpp"

#include <cstdint>

namespace OmicronTK {
namespace lua {

void LuaRegVector_forEach(lua_State *L, const ValueMap &values);

void pcall(lua_State *state, const std::string &name, const ValueVec &values, size_t returnsSize);
void pcallTable(lua_State *state, bool isObject, const std::string &table, const std::string &field,
                const ValueVec &values, size_t returnsSize);
ValueVec pcallReturn(lua_State *state, const std::vector<ValueType> &returns);

Value toValue(lua_State *state, ValueType type, uint32_t idx);

void pushValue(lua_State *state, const Value &value);

template<const ValueType _type>
_ValueType<_type> toValue(lua_State *state, uint32_t idx)
{
    return toValue(state, _type, idx).value<_type>();
}

}
}
