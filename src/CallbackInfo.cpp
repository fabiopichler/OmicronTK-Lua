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

void CallbackInfo::required(int value) const
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

void CallbackInfo::required(int min, int max) const
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

double CallbackInfo::getNumber(int idx, double defaultValue) const
{
    if (m_length >= idx)
    {
        luaL_checktype(m_state, idx, LUA_TNUMBER);
        return double (lua_tonumber(m_state, idx));
    }

    return defaultValue;
}

float CallbackInfo::getFloat(int idx, float defaultValue) const
{
    if (m_length >= idx)
    {
        luaL_checktype(m_state, idx, LUA_TNUMBER);
        return float (lua_tonumber(m_state, idx));
    }

    return defaultValue;
}

int CallbackInfo::getInteger(int idx, int defaultValue) const
{
    if (m_length >= idx)
    {
        luaL_checktype(m_state, idx, LUA_TNUMBER);
        return int (lua_tointeger(m_state, idx));
    }

    return defaultValue;
}

unsigned int CallbackInfo::getUInt(int idx, unsigned int defaultValue) const
{
    if (m_length >= idx)
    {
        luaL_checktype(m_state, idx, LUA_TNUMBER);
        return static_cast<unsigned int>(lua_tonumber(m_state, idx));
    }

    return defaultValue;
}

long CallbackInfo::getLong(int idx, long defaultValue) const
{
    if (m_length >= idx)
    {
        luaL_checktype(m_state, idx, LUA_TNUMBER);
        return long (lua_tonumber(m_state, idx));
    }

    return defaultValue;
}

unsigned long CallbackInfo::getULong(int idx, unsigned long defaultValue) const
{
    if (m_length >= idx)
    {
        luaL_checktype(m_state, idx, LUA_TNUMBER);
        return static_cast<unsigned long>(lua_tonumber(m_state, idx));
    }

    return defaultValue;
}

const char *CallbackInfo::getCString(int idx, const char *defaultValue) const
{
    if (m_length >= idx)
        return luaL_checklstring(m_state, idx, nullptr);

    return defaultValue;
}

std::string CallbackInfo::getString(int idx, const std::string &defaultValue) const
{
    if (m_length >= idx)
        return luaL_checklstring(m_state, idx, nullptr);

    return defaultValue;
}

lua_CFunction CallbackInfo::getCFunction(int idx, lua_CFunction defaultValue) const
{
    if (m_length >= idx)
    {
        luaL_checktype(m_state, idx, LUA_TFUNCTION);
        return lua_tocfunction(m_state, idx);
    }

    return defaultValue;
}

bool CallbackInfo::getBoolean(int idx, bool defaultValue) const
{
    if (m_length >= idx)
    {
        luaL_checktype(m_state, idx, LUA_TBOOLEAN);
        return bool (lua_toboolean(m_state, idx));
    }

    return defaultValue;
}

void *CallbackInfo::getUserData(int idx, void *defaultValue) const
{
    if (m_length >= idx)
    {
        lua_getfield(m_state, idx, "__userdata");
        luaL_checktype(m_state, -1, LUA_TUSERDATA);

        return *static_cast<void **>(lua_touserdata(m_state, -1));
    }

    return defaultValue;
}

void *CallbackInfo::getLightUserData(int idx, void *defaultValue) const
{
    if (m_length >= idx)
    {
        luaL_checktype(m_state, idx, LUA_TLIGHTUSERDATA);
        return lua_touserdata(m_state, idx);
    }

    return defaultValue;
}

}
}
