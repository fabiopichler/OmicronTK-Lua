/*******************************************************************************
  OmicronTK+Lua

  Author: Fábio Pichler
  Website: http://fabiopichler.net
  License: The MIT License

  Copyright 2018-2019, Fábio Pichler

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
#include <vector>

typedef struct lua_State lua_State;

namespace OmicronTK {
namespace OTKLUA {

using LuaCFunction = int (*)(lua_State *);

struct LuaReg
{
    const char *name;
    LuaCFunction func;
};

using LuaRegVector = std::vector<LuaReg>;

class OTKLUA_EXPORT LuaState
{
public:
    LuaState();
    ~LuaState();

    inline lua_State *state() const { return m_state; }

    bool loadFile(const std::string &fileName);
    bool execute(const std::string &script);

    void push(const std::string &name, const std::string &value);
    void push(const std::string &name, int value);
    void push(const std::string &name, void *value);
    void push(const std::string &name, LuaCFunction value);

    int addDirPath(const std::string &path);

    void reg(const std::string &name, const LuaRegVector &functions, const LuaRegVector &methods = LuaRegVector());

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
