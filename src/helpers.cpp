#include "OmicronTK/lua/helpers.hpp"

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

void pcall(lua_State *state, const std::string &name, const LuaValueVector &values, size_t returnsSize)
{
    lua_getglobal(state, name.c_str());

    for (const auto &value : values)
        pushLuaValue(state, value);

    lua_pcall(state, values.size(), returnsSize, 0);
}

void pcallTable(lua_State *state, bool isObject, const std::string &table, const std::string &field,
                const LuaValueVector &values, size_t returnsSize)
{
    lua_getglobal(state, table.c_str());
    lua_getfield(state, -1, field.c_str());

    size_t valuesSize = values.size();

    if (isObject)
    {
        ++valuesSize;
        lua_pushvalue(state, -2);
    }
    else
    {
        lua_pushvalue(state, -1);
    }

    for (const auto &value : values)
        pushLuaValue(state, value);

    lua_pcall(state, valuesSize, returnsSize, 0);
}

LuaValueVector pcallReturn(lua_State *state, const std::vector<LuaValue::Type> &returns)
{
    LuaValueVector valueVector;

    for (size_t idx = 0; idx < returns.size(); ++idx)
        valueVector.push_back(toLuaValue(state, returns[idx], idx + 1));

    lua_settop(state, 0);

    return valueVector;
}

LuaValue toLuaValue(lua_State *state, LuaValue::Type type, uint32_t idx)
{
    switch (type) {
        case LuaValue::Undefined:
        case LuaValue::Nil:
        break;

        case LuaValue::Number:
            return double(lua_tonumber(state, idx));

        case LuaValue::Integer:
            return int(lua_tointeger(state, idx));

        case LuaValue::String:
        {
            if (lua_isnil(state, idx))
                return EmptyString;

            return lua_tostring(state, idx);
        }

        case LuaValue::CFunction:
            return lua_tocfunction(state, idx);

        case LuaValue::Boolean:
            return bool(lua_toboolean(state, idx));

        case LuaValue::UserData:
        {
            if (lua_isuserdata(state, idx))
                return *static_cast<void **>(lua_touserdata(state, idx));

            if (lua_islightuserdata(state, idx))
                return lua_touserdata(state, idx);

            return static_cast<void *>(nullptr);
        }
    }

    return LuaValue(0);
}

void pushLuaValue(lua_State *state, const LuaValue &value)
{
    switch (value.type()) {
        case LuaValue::Undefined:
        break;

        case LuaValue::Nil:
            lua_pushnil(state);
        break;

        case LuaValue::Number:
            lua_pushnumber(state, value.number_value());
        break;

        case LuaValue::Integer:
            lua_pushinteger(state, value.integer_value());
        break;

        case LuaValue::String:
            lua_pushstring(state, value.string_value().c_str());
        break;

        case LuaValue::CFunction:
            lua_pushcfunction(state, value.cfunction_value());
        break;

        case LuaValue::Boolean:
            lua_pushboolean(state, value.boolean_value());
        break;

        case LuaValue::UserData:
            lua_pushlightuserdata(state, value.userdata_value());
        break;
    }
}

}
}
