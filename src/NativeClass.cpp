#include "OmicronTK/lua/NativeClass.hpp"
#include "OmicronTK/lua/Lua.hpp"
#include "OmicronTK/lua/helpers.hpp"

#include <lua.hpp>

namespace OmicronTK {
namespace lua {

NativeClass::NativeClass(Lua &lua, const std::string &name)
    : m_lua(lua)
    , m_name(name) {}

void NativeClass::setStatics(const RegMap &statics)
{
    m_statics = statics;
}

void NativeClass::addStatic(const std::string &field, const Value &value)
{
    m_statics[field] = value;
}

void NativeClass::setMembers(const RegMap &members)
{
    m_members = members;
}

void NativeClass::addMember(const std::string &field, const Value &value)
{
    m_members[field] = value;
}

void NativeClass::setMetamethods(const RegMap &metamethods)
{
    m_metamethods = metamethods;
}

void NativeClass::addMetamethod(const std::string &field, const Value &value)
{
    m_metamethods[field] = value;
}

void NativeClass::addConstructor(const Value &constructor)
{
    m_members["constructor"] = constructor;
}

void NativeClass::addDestructor(const Value &__gc)
{
    m_metamethods["__gc"] = __gc;
}

void NativeClass::create()
{
    lua_State *state = m_lua.state();

    pcall(state, "class", { m_name.c_str() }, 1);

    LuaRegVector_forEach(state, m_statics);

    if (!m_members.empty())
    {
        lua_getfield(state, -1, "proto");
        LuaRegVector_forEach(state, m_members);
        lua_pop(state, 1);
    }

    lua_setglobal(state, m_name.c_str());
    luaL_newmetatable(state, m_name.c_str());

    lua_pushvalue(state, -1);
    lua_setfield(state, -2, "__index");
    LuaRegVector_forEach(state, m_metamethods);

    lua_pop(state, 1);
}

}
}
