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

double CallbackInfo::getNumber(int idx)
{
    luaL_checktype(m_state, idx, LUA_TNUMBER);
    return double (lua_tonumber(m_state, idx));
}

float CallbackInfo::getFloat(int idx)
{
    luaL_checktype(m_state, idx, LUA_TNUMBER);
    return float (lua_tonumber(m_state, idx));
}

int CallbackInfo::getInteger(int idx)
{
    luaL_checktype(m_state, idx, LUA_TNUMBER);
    return int (lua_tointeger(m_state, idx));
}

unsigned int CallbackInfo::getUInt(int idx)
{
    luaL_checktype(m_state, idx, LUA_TNUMBER);
    return static_cast<unsigned int>(lua_tonumber(m_state, idx));
}

long CallbackInfo::getLong(int idx)
{
    luaL_checktype(m_state, idx, LUA_TNUMBER);
    return long (lua_tonumber(m_state, idx));
}

unsigned long CallbackInfo::getULong(int idx)
{
    luaL_checktype(m_state, idx, LUA_TNUMBER);
    return static_cast<unsigned long>(lua_tonumber(m_state, idx));
}

const char *CallbackInfo::getCString(int idx)
{
    return luaL_checklstring(m_state, idx, nullptr);
}

std::string CallbackInfo::getString(int idx)
{
    return luaL_checklstring(m_state, idx, nullptr);
}

lua_CFunction CallbackInfo::getCFunction(int idx)
{
    luaL_checktype(m_state, idx, LUA_TFUNCTION);
    return lua_tocfunction(m_state, idx);
}

bool CallbackInfo::getBoolean(int idx)
{
    luaL_checktype(m_state, idx, LUA_TBOOLEAN);
    return bool (lua_toboolean(m_state, idx));
}

void *CallbackInfo::getUserData(int idx)
{
    lua_getfield(m_state, idx, "__userdata");
    luaL_checktype(m_state, -1, LUA_TUSERDATA);

    return *static_cast<void **>(lua_touserdata(m_state, -1));
}

void *CallbackInfo::getLightUserData(int idx)
{
    luaL_checktype(m_state, idx, LUA_TLIGHTUSERDATA);
    return lua_touserdata(m_state, idx);
}

}
}
