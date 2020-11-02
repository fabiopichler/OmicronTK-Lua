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

#include "OmicronTK/lua/LuaState.hpp"
#include "private/helpers.hpp"

#include <lua.hpp>
#include <iostream>

namespace OmicronTK {
namespace lua {

LuaState::LuaState()
{
    m_state = luaL_newstate();
    luaL_openlibs(m_state);
}

LuaState::~LuaState()
{
    if (m_state)
        lua_close(m_state);
}

bool LuaState::loadFile(const std::string &fileName)
{
    if (luaL_dofile(m_state, fileName.c_str()) == LUA_OK)
        return true;

    std::cerr << "[LuaState::loadFile] error: " << lua_tostring(m_state, -1) << std::endl;

    lua_close(m_state);
    m_state = nullptr;

    return false;
}

bool LuaState::execute(const std::string &script)
{
    if (luaL_dostring(m_state, script.c_str()) == LUA_OK)
        return true;

    std::cerr << "[LuaState::execute] error: " << lua_tostring(m_state, -1) << std::endl;
    return false;
}

void LuaState::setGlobal(const std::string &name, const LuaValue &value)
{
    pushLuaValue(m_state, value);
    lua_setglobal(m_state, name.c_str());
}

LuaValue LuaState::getGlobal(const std::string &name, LuaValueType type)
{
    lua_getglobal(m_state, name.c_str());

    return toLuaValue(m_state, type, 1);
}

void LuaState::call(const std::string &name, const LuaValueVector &values)
{
    lua_getglobal(m_state, name.c_str());

    for (const auto &value : values)
        pushLuaValue(m_state, value);

    lua_pcall(m_state, values.size(), 0, 0);
}

LuaValueVector LuaState::call(const std::string &name, const LuaValueVector &values, std::vector<LuaValueType> returns)
{
    lua_getglobal(m_state, name.c_str());

    for (const auto &value : values)
        pushLuaValue(m_state, value);

    lua_pcall(m_state, values.size(), returns.size(), 0);

    LuaValueVector valueVector;

    for (size_t idx = 1; idx <= returns.size(); ++idx)
        valueVector.push_back(toLuaValue(m_state, returns[idx - 1], idx));

    return valueVector;
}

int LuaState::addDirPath(const std::string &path)
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

void LuaState::reg(const std::string &name, const LuaRegVector &functions, const LuaRegVector &methods)
{
    lua_newtable(m_state);
    LuaRegVector_forEach(m_state, functions);
    lua_setglobal(m_state, name.c_str());

    luaL_newmetatable(m_state, name.c_str());

    if (!methods.empty())
    {
        lua_pushvalue(m_state, -1);
        lua_setfield(m_state, -2, "__index");
        LuaRegVector_forEach(m_state, methods);
    }

    lua_pop(m_state, 1);
}

}
}
