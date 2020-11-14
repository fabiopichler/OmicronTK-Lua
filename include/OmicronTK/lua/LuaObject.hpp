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
#include "OmicronTK/lua/util/LuaUtil.hpp"
#include "OmicronTK/lua/helpers.hpp"

#include <vector>

namespace OmicronTK {
namespace lua {

template<typename _Class, const char *_className>
class LuaObject
{
public:
    template<const LuaValue::Type... _types>
    inline static int constructor(lua_State *L)
    {
        std::vector<LuaValue> args;
        forEach<_types...>(L, 1, args);

        _Class *object = callConstructor(args, std::make_index_sequence<sizeof... (_types)>{});

        LuaUtil::newUserData<_Class>(L, _className, object);

        return 1;
    }

    template<typename _Method, const _Method *_method, const LuaValue::Type... _types>
    inline static int method(lua_State *L)
    {
        _Class *object = LuaUtil::checkUserData<_Class>(L, 1, _className);

        std::vector<LuaValue> args;
        forEach<_types...>(L, 2, args);

        callMethod(object, _method, args, std::make_index_sequence<sizeof... (_types)>{});

        return 0;
    }

    template<typename _Method, const _Method *_method, const LuaValue::Type _returnType, const LuaValue::Type... _types>
    inline static int method_r(lua_State *L)
    {
        _Class *object = LuaUtil::checkUserData<_Class>(L, 1, _className);

        std::vector<LuaValue> args;
        forEach<_types...>(L, 2, args);

        LuaValue valueReturn = callMethod_r(object, _method, args, std::make_index_sequence<sizeof... (_types)>{});

        pushLuaValue(L, valueReturn);

        return 1;
    }

private:
    template<const LuaValue::Type... _types>
    inline static void forEach(lua_State *L, uint32_t index, std::vector<LuaValue> &args)
    {
        const LuaValue::Type types[] = { _types... };

        for (const LuaValue::Type &type : types)
        {
            args.push_back(toLuaValue(L, type, index));
            ++index;
        }
    }

    template<typename _Args, std::size_t... I>
    inline static _Class *callConstructor(_Args&& _args, std::index_sequence<I...>)
    {
        return new _Class(_args[I]...);
    }

    template<typename _Method, typename _Args, std::size_t... I>
    inline static void callMethod(_Class *_object, _Method&& _method, _Args&& _args, std::index_sequence<I...>)
    {
        (_object->*(*_method))(_args[I]...);
    }

    template<typename _Method, typename _Args, std::size_t... I>
    inline static auto callMethod_r(_Class *_object, _Method&& _method, _Args&& _args, std::index_sequence<I...>)
    {
        return std::forward<LuaValue>((_object->*(*_method))(_args[I]...));
    }
};

}
}
