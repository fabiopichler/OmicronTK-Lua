/*---------------------------------------------------------------------------

Copyright (c) 2020 Fábio Pichler

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-----------------------------------------------------------------------------*/

#pragma once

#include "OmicronTK/lua/LuaValue.hpp"
#include "OmicronTK/lua/util/LuaObjUtil.hpp"
#include "OmicronTK/lua/helpers.hpp"

#include <cassert>

namespace OmicronTK {
namespace lua {

template<typename _Class, const char *_className>
class LuaObject
{
    using ObjUtil = LuaObjUtil<_Class, _className>;

public:
    template<const LuaValue::Type... _types>
    inline static int constructor(lua_State *L)
    {
        assert ((lua_gettop(L) - 1) == (sizeof... (_types)));

        luaL_checktype(L, 1, LUA_TTABLE);

        auto args = argsFunc<_types...>(L);
        _Class *object = callConstructor(args, std::make_index_sequence<sizeof... (_types)>{});

        lua_pushvalue(L, 1);
        ObjUtil::newUserData(L, object);

        return 0;
    }

    template<typename _Method, const _Method *_method, const LuaValue::Type... _types>
    inline static int method(lua_State *L)
    {
        _Class *object = getUserData<_types...>(L);
        auto args = argsFunc<_types...>(L);

        callMethod(object, _method, args, std::make_index_sequence<sizeof... (_types)>{});

        return 0;
    }

    template<typename _Method, const _Method *_method, const LuaValue::Type _returnType, const LuaValue::Type... _types>
    inline static int method_r(lua_State *L)
    {
        _Class *object = getUserData<_types...>(L);
        auto args = argsFunc<_types...>(L);

        LuaValue val = callMethod_r(object, _method, args, std::make_index_sequence<sizeof... (_types)>{});

        pushLuaValue(L, val);

        return 1;
    }

    inline static int __gc(lua_State *L)
    {
        _Class *object = *static_cast<_Class **>(luaL_checkudata(L, -1, _className));

        if (object)
        {
            delete object;
            return 0;
        }

        lua_pushstring(L, "C++ object garbage failure");
        lua_error(L);
        return 0;
    }

    class util
    {
    public:
        template<const LuaValue::Type... _types>
        inline static LuaReg constructor()
        {
            return LuaReg { "constructor", LuaObject::constructor<_types...> };
        }

        static inline LuaReg __gc()
        {
            return LuaReg { "__gc", LuaObject::__gc };
        }
    };

private:
    template<const LuaValue::Type... _types>
    inline static _Class *getUserData(lua_State *L)
    {
        assert ((lua_gettop(L) - 1) == (sizeof... (_types)));

        return ObjUtil::checkUserData(L, 1);
    }

    template<const LuaValue::Type... _types>
    inline static auto argsFunc(lua_State *L)
    {
        const LuaValue::Type types[] { _types... };

        return [types, L] (int i) {
            return toLuaValue(L, types[i], i + 2);
        };
    }

    template<typename _ArgsFunc, std::size_t... I>
    inline static _Class *callConstructor(_ArgsFunc&& _args, std::index_sequence<I...>)
    {
        return new _Class(_args(I)...);
    }

    template<typename _Method, typename _ArgsFunc, std::size_t... I>
    inline static void callMethod(_Class *_object, _Method&& _method, _ArgsFunc&& _args, std::index_sequence<I...>)
    {
        (_object->*(*_method))(_args(I)...);
    }

    template<typename _Method, typename _ArgsFunc, std::size_t... I>
    inline static auto callMethod_r(_Class *_object, _Method&& _method, _ArgsFunc&& _args, std::index_sequence<I...>)
    {
        return std::forward<LuaValue>((_object->*(*_method))(_args(I)...));
    }
};

}
}
