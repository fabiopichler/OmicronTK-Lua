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
#include "OmicronTK/lua/Value.hpp"
#include "OmicronTK/lua/Class.hpp"

namespace OmicronTK {
namespace lua {

class OTKLUA_EXPORT Lua
{
public:
    Lua();
    ~Lua();

    inline lua_State *state() { return m_state; }

    void close();
    bool executeFile(const std::string &fileName);
    bool execute(const std::string &script);

    void createTable(const std::string &name, const RegVector &values = {});
    void createClass(const Class &luaClass);

    void setValue(const std::string &global, const Value &value);
    void setValue(const std::string &table, const std::string &field, const Value &value);
    void setValues(const std::string &table, const RegVector &values);

    void addToPrototype(const std::string &table, const std::string &field, const Value &value);
    void addToPrototype(const std::string &table, const RegVector &values);

    Value getValue(const std::string &global, ValueType type);
    Value getValue(const std::string &table, const std::string &field, ValueType type);

    void callFunction(const std::string &name, const ValueVector &values = {}, size_t returns = 0);
    ValueVector callFunction(const std::string &name, const ValueVector &values,
                                const std::vector<ValueType> &returns);

    void callTableFunction(const std::string &table, const std::string &field,
                           const ValueVector &values = {}, size_t returns = 0);
    ValueVector callTableFunction(const std::string &table, const std::string &field,
                                     const ValueVector &values, const std::vector<ValueType> &returns);

    void callObjectMethod(const std::string &table, const std::string &field,
                          const ValueVector &values = {}, size_t returns = 0);
    ValueVector callObjectMethod(const std::string &table, const std::string &field,
                                    const ValueVector &values, const std::vector<ValueType> &returns);

    void addDirPath(const std::string &path);

    template<typename LuaClass>
    inline void require()
    {
        LuaClass::require(this);
    }

private:
    lua_State *m_state;
};

}
}
