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

#pragma once

#include "global.h"

#include <string>

#include "OmicronTK/lua/defines.hpp"
#include "OmicronTK/lua/LuaValue.hpp"

namespace OmicronTK {
namespace lua {

class OTKLUA_EXPORT Lua
{
public:
    Lua();
    ~Lua();

    inline lua_State *getState() { return m_state; }

    bool executeFile(const std::string &fileName);
    bool execute(const std::string &script);

    void setValue(const std::string &name, const LuaValue &value);
    LuaValue getValue(const std::string &name, LuaValue::Type type);
    void createTable(const std::string &table, const LuaRegVector &statics,
                     const LuaRegVector &members = {}, const LuaRegVector &metamethods = {});
    void addToTable(const std::string &table, const std::string &field, const LuaValue &value);
    void addToTable(const std::string &table, const LuaRegVector &statics);

    void callFunction(const std::string &name, const LuaValueVector &values = {}, size_t returns = 0);
    LuaValueVector callFunction(const std::string &name, const LuaValueVector &values,
                                const std::vector<LuaValue::Type> &returns);

    void callTableFunction(const std::string &table, const std::string &field,
                           const LuaValueVector &values = {}, size_t returns = 0);
    LuaValueVector callTableFunction(const std::string &table, const std::string &field,
                                     const LuaValueVector &values, const std::vector<LuaValue::Type> &returns);

    void callObjectMethod(const std::string &table, const std::string &field,
                          const LuaValueVector &values = {}, size_t returns = 0);
    LuaValueVector callObjectMethod(const std::string &table, const std::string &field,
                                    const LuaValueVector &values, const std::vector<LuaValue::Type> &returns);

    int addDirPath(const std::string &path);

    template<typename LuaClass>
    inline void requiref()
    {
        LuaClass::requiref(this);
    }

private:
    lua_State *m_state;
};

}
}
