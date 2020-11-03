#include "helpers.hpp"

#include <string>
#include <lua.hpp>

namespace OmicronTK {
namespace lua {

void LuaRegVector_forEach(lua_State *L, const LuaRegVector &values)
{
    for (const LuaReg &value : values)
    {
        pushLuaValue(L, value.value);
        lua_setfield(L, -2, value.name);
    }
}

LuaValue toLuaValue(lua_State *state, LuaValueType type, uint32_t idx)
{
    switch (type) {
        case LuaValueType::Undefined:
        case LuaValueType::Nil:
        break;

        case LuaValueType::Number:
            return double(lua_tonumber(state, idx));

        case LuaValueType::Integer:
            return int(lua_tointeger(state, idx));

        case LuaValueType::String:
        {
            if (lua_isnil(state, idx))
                return EmptyString;

            return lua_tostring(state, idx);
        }

        case LuaValueType::CFunction:
            return lua_tocfunction(state, idx);

        case LuaValueType::Boolean:
            return bool(lua_toboolean(state, idx));

        case LuaValueType::Lightuserdata:
            return lua_touserdata(state, idx);
    }

    return LuaValue(0);
}

void pushLuaValue(lua_State *state, const LuaValue &value)
{
    switch (value.type()) {
        case LuaValueType::Undefined:
        break;

        case LuaValueType::Nil:
            lua_pushnil(state);
        break;

        case LuaValueType::Number:
            lua_pushnumber(state, value.number_value());
        break;

        case LuaValueType::Integer:
            lua_pushinteger(state, value.integer_value());
        break;

        case LuaValueType::String:
            lua_pushstring(state, value.string_value().c_str());
        break;

        case LuaValueType::CFunction:
            lua_pushcfunction(state, value.cfunction_value());
        break;

        case LuaValueType::Boolean:
            lua_pushboolean(state, value.boolean_value());
        break;

        case LuaValueType::Lightuserdata:
            lua_pushlightuserdata(state, value.lightuserdata_value());
        break;
    }
}

}
}
