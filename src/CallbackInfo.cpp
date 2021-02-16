#include "OmicronTK/lua/CallbackInfo.hpp"
#include <OmicronTK/lua/helpers.hpp>

#include <lua.hpp>

#include <stdexcept>

namespace OmicronTK {
namespace lua {

CallbackInfo::ReturnValue::ReturnValue(lua_State *L)
    : m_state(L)
    , m_length(0)
{
}

void CallbackInfo::ReturnValue::add(const Value &value)
{
    pushValue(m_state, value);
    ++m_length;
}

CallbackInfo::CallbackInfo(lua_State *L)
    : m_state(L)
    , m_length(lua_gettop(L))
    , m_returnValue(L)
{
}

CallbackInfo::~CallbackInfo()
{
}

void CallbackInfo::required(int value)
{
    if (m_length != value)
    {
        std::string message;
        message.append("expecting exactly ")
                .append(std::to_string(value))
                .append(" arguments");

        throw std::logic_error(message);
    }
}

void CallbackInfo::required(int min, int max)
{
    if (m_length < min || m_length > max)
    {
        std::string message;
        message.append("expecting between ")
                .append(std::to_string(min))
                .append(" and ")
                .append(std::to_string(max))
                .append(" arguments");

        throw std::logic_error(message);
    }
}

double CallbackInfo::getNumber(int idx, bool required, double defaultValue) const
{
    luaL_checktype(m_state, idx, LUA_TNUMBER);
    return double (lua_tonumber(m_state, idx));
}

float CallbackInfo::getFloat(int idx, bool required, float defaultValue) const
{
    luaL_checktype(m_state, idx, LUA_TNUMBER);
    return float (lua_tonumber(m_state, idx));
}

int CallbackInfo::getInteger(int idx, bool required, int defaultValue) const
{
    luaL_checktype(m_state, idx, LUA_TNUMBER);
    return int (lua_tointeger(m_state, idx));
}

unsigned int CallbackInfo::getUInt(int idx, bool required, unsigned int defaultValue) const
{
    luaL_checktype(m_state, idx, LUA_TNUMBER);
    return static_cast<unsigned int>(lua_tonumber(m_state, idx));
}

long CallbackInfo::getLong(int idx, bool required, long defaultValue) const
{
    luaL_checktype(m_state, idx, LUA_TNUMBER);
    return long (lua_tonumber(m_state, idx));
}

unsigned long CallbackInfo::getULong(int idx, bool required, unsigned long defaultValue) const
{
    luaL_checktype(m_state, idx, LUA_TNUMBER);
    return static_cast<unsigned long>(lua_tonumber(m_state, idx));
}

const char *CallbackInfo::getCString(int idx, bool required, const char *defaultValue) const
{
    return luaL_checklstring(m_state, idx, nullptr);
}

std::string CallbackInfo::getString(int idx, bool required, std::string defaultValue) const
{
    return luaL_checklstring(m_state, idx, nullptr);
}

lua_CFunction CallbackInfo::getCFunction(int idx, bool required, lua_CFunction defaultValue) const
{
    luaL_checktype(m_state, idx, LUA_TFUNCTION);
    return lua_tocfunction(m_state, idx);
}

bool CallbackInfo::getBoolean(int idx, bool required, bool defaultValue) const
{
    luaL_checktype(m_state, idx, LUA_TBOOLEAN);
    return bool (lua_toboolean(m_state, idx));
}

void *CallbackInfo::getUserData(int idx, bool required, void *defaultValue) const
{
    lua_getfield(m_state, idx, "__userdata");
    luaL_checktype(m_state, -1, LUA_TUSERDATA);

    return *static_cast<void **>(lua_touserdata(m_state, -1));
}

void *CallbackInfo::getLightUserData(int idx, bool required, void *defaultValue) const
{
    luaL_checktype(m_state, idx, LUA_TLIGHTUSERDATA);
    return lua_touserdata(m_state, idx);
}

}
}
