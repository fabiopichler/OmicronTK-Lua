#pragma once

#include "OmicronTK/lua/LuaValue.hpp"
#include "OmicronTK/lua/helpers.hpp"

#include <lua.hpp>
#include <cassert>

namespace OmicronTK {
namespace lua {

class LuaFunctional
{
public:
    template<typename _Func, const _Func *_func, const LuaValue::Type... _types>
    inline static int function(lua_State *L)
    {
        assert (lua_gettop(L) == (sizeof... (_types)));

        auto args = argsFunc<_types...>(L);
        callFunction(_func, args, std::make_index_sequence<sizeof... (_types)>{});

        return 0;
    }

    template<typename _Func, const _Func *_func, const LuaValue::Type _returnType, const LuaValue::Type... _types>
    inline static int function_r(lua_State *L)
    {
        assert (lua_gettop(L) == (sizeof... (_types)));

        auto args = argsFunc<_types...>(L);
        LuaValue val = callFunction_r(_func, args, std::make_index_sequence<sizeof... (_types)>{});

        pushLuaValue(L, val);

        return 1;
    }

private:
    template<const LuaValue::Type... _types>
    inline static auto argsFunc(lua_State *L)
    {
        const LuaValue::Type types[] { _types... };

        return [types, L] (int i) {
            return toLuaValue(L, types[i], i + 1);
        };
    }

    template<typename _Func, typename _ArgsFunc, std::size_t... I>
    inline static void callFunction(_Func&& _func, _ArgsFunc&& _args, std::index_sequence<I...>)
    {
        _func(_args(I)...);
    }

    template<typename _Func, typename _ArgsFunc, std::size_t... I>
    inline static auto callFunction_r(_Func&& _func, _ArgsFunc&& _args, std::index_sequence<I...>)
    {
        return std::forward<LuaValue>(_func(_args(I)...));
    }
};

}
}
