/*******************************************************************************
  OmicronTK_lua

  Author: Fábio Pichler
  Website: http://fabiopichler.net
  License: The MIT License

  Copyright 2018-2020, Fábio Pichler

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the Software
  is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
  THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*******************************************************************************/

#include "OmicronTK/lua/Lua.hpp"
#include "OmicronTK/lua/helpers.hpp"

#include <lua.hpp>
#include <iostream>

namespace OmicronTK {
namespace lua {

static const char *lib_class =
    #include "private/lib_class.lua"
;

Lua::Lua()
{
    m_state = luaL_newstate();

    luaL_openlibs(m_state);
    execute(lib_class);
}

Lua::~Lua()
{
    if (m_state)
        lua_close(m_state);
}

bool Lua::executeFile(const std::string &fileName)
{
    if (luaL_dofile(m_state, fileName.c_str()) == LUA_OK)
        return true;

    std::cerr << "[LuaState::loadFile] error: " << lua_tostring(m_state, -1) << std::endl;

    lua_close(m_state);
    m_state = nullptr;

    return false;
}

bool Lua::execute(const std::string &script)
{
    if (luaL_dostring(m_state, script.c_str()) == LUA_OK)
        return true;

    std::cerr << "[LuaState::execute] error: " << lua_tostring(m_state, -1) << std::endl;
    return false;
}

void Lua::createTable(const std::string &name, const LuaRegVector &values)
{
    lua_newtable(m_state);
    LuaRegVector_forEach(m_state, values);
    lua_setglobal(m_state, name.c_str());
}

void Lua::createClass(const std::string &name, const LuaRegVector &statics,
                      const LuaRegVector &members, const LuaRegVector &metamethods)
{
    pcall(m_state, "class", { name.c_str() }, 1);

    LuaRegVector_forEach(m_state, statics);

    if (!members.empty())
    {
        lua_getfield(m_state, -1, "proto");
        LuaRegVector_forEach(m_state, members);
        lua_pop(m_state, 1);
    }

    lua_setglobal(m_state, name.c_str());
    luaL_newmetatable(m_state, name.c_str());

    lua_pushvalue(m_state, -1);
    lua_setfield(m_state, -2, "__index");
    LuaRegVector_forEach(m_state, metamethods);

    lua_pop(m_state, 1);
}

void Lua::setValue(const std::string &global, const LuaValue &value)
{
    pushLuaValue(m_state, value);
    lua_setglobal(m_state, global.c_str());
}

void Lua::setValue(const std::string &table, const std::string &field, const LuaValue &value)
{
    setValues(table, { {field.c_str(), value} });
}

void Lua::setValues(const std::string &table, const LuaRegVector &values)
{
    lua_getglobal(m_state, table.c_str());
    LuaRegVector_forEach(m_state, values);
    lua_pop(m_state, 1);
}

void Lua::addToPrototype(const std::string &table, const std::string &field, const LuaValue &value)
{
    addToPrototype(table, { {field.c_str(), value} });
}

void Lua::addToPrototype(const std::string &table, const LuaRegVector &values)
{
    lua_getglobal(m_state, table.c_str());
    lua_getfield(m_state, -1, "proto");

    LuaRegVector_forEach(m_state, values);

    lua_pop(m_state, 1);
}

LuaValue Lua::getValue(const std::string &global, LuaValue::Type type)
{
    lua_getglobal(m_state, global.c_str());
    LuaValue value = toLuaValue(m_state, type, 1);

    lua_pop(m_state, 1);

    return value;
}

LuaValue Lua::getValue(const std::string &table, const std::string &field, LuaValue::Type type)
{
    lua_getglobal(m_state, table.c_str());
    lua_getfield(m_state, -1, field.c_str());

    LuaValue value = toLuaValue(m_state, type, 1);

    lua_pop(m_state, 1);

    return value;
}

void Lua::callFunction(const std::string &name, const LuaValueVector &values, size_t returns)
{
    pcall(m_state, name, values, returns);
}

LuaValueVector Lua::callFunction(const std::string &name, const LuaValueVector &values,
                                 const std::vector<LuaValue::Type> &returns)
{
    pcall(m_state, name, values, returns.size());
    return pcallReturn(m_state, returns);
}

void Lua::callTableFunction(const std::string &table, const std::string &field,
                            const LuaValueVector &values, size_t returns)
{
    pcallTable(m_state, false, table, field, values, returns);
}

LuaValueVector Lua::callTableFunction(const std::string &table, const std::string &field,
                                 const LuaValueVector &values, const std::vector<LuaValue::Type> &returns)
{
    pcallTable(m_state, false, table, field, values, returns.size());
    return pcallReturn(m_state, returns);
}

void Lua::callObjectMethod(const std::string &table, const std::string &field,
                           const LuaValueVector &values, size_t returns)
{
    pcallTable(m_state, true, table, field, values, returns);
}

LuaValueVector Lua::callObjectMethod(const std::string &table, const std::string &field,
                                const LuaValueVector &values, const std::vector<LuaValue::Type> &returns)
{
    pcallTable(m_state, false, table, field, values, returns.size());
    return pcallReturn(m_state, returns);
}

int Lua::addDirPath(const std::string &path)
{
    lua_getglobal(m_state, "package");
    lua_getfield(m_state, -1, "path");

    std::string cur_path = lua_tostring(m_state, -1);
    cur_path.append(";").append(path).append("?.lua");

    lua_pop(m_state, 1);

    lua_pushstring(m_state, cur_path.c_str());
    lua_setfield(m_state, -2, "path");

    lua_pop(m_state, 1);

    return 0;
}

}
}
