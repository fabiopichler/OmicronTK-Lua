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

#include <lua.hpp>
#include <vector>

namespace OmicronTK {
namespace lua {

class OTKLUA_EXPORT LuaBase
{
public:
    template<typename LuaClass>
    static inline void newUserData(lua_State *L, const char *tableName, void *userdata)
    {
        *static_cast<void **>(lua_newuserdata(L, sizeof(LuaClass *))) = userdata;
        luaL_setmetatable(L, tableName);
    }

    template<typename LuaClass>
    static inline LuaClass *checkUserData(lua_State *L, int ud, const char *tableName)
    {
        return *static_cast<LuaClass **>(luaL_checkudata(L, ud, tableName));
    }

    template<typename LuaClass>
    static inline int __gc(lua_State *L, const char *tableName)
    {
        LuaClass *userdata = checkUserData<LuaClass>(L, 1, tableName);

        if (userdata)
        {
            delete userdata;
        }
        else
        {
            lua_pushstring(L, "C++ object garbage failure");
            lua_error(L);
        }

        return 0;
    }
};

}
}
