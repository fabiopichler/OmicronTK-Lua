#pragma once

#include "OmicronTK/lua/Value.hpp"
#include "OmicronTK/lua/helpers.hpp"

#include <lua.hpp>
#include <utility>
#include <cassert>

namespace OmicronTK {
namespace lua {

class Functional
{
public:
    template<typename _Func, const _Func *_func, const ValueType... _types>
    inline static int function(lua_State *L)
    {
        assert (lua_gettop(L) == (sizeof... (_types)));

        callFunction<_types...>(L, _func, std::make_index_sequence<sizeof... (_types)>{});

        return 0;
    }

    template<typename _Func, const _Func *_func, const ValueType _returnType, const ValueType... _types>
    inline static int function_r(lua_State *L)
    {
        assert (lua_gettop(L) == (sizeof... (_types)));

        Value val = callFunction_r<_types...>(L, _func, std::make_index_sequence<sizeof... (_types)>{});

        pushValue(L, val);

        return 1;
    }

private:
    template<const ValueType... _types, typename _Func, std::size_t... I>
    inline static void callFunction(lua_State *L, _Func&& _func, std::index_sequence<I...>)
    {
        const ValueType types[] { _types... };

        (*_func)(std::forward<Value>(toValue(L, types[I], I + 1))...);
    }

    template<const ValueType... _types, typename _Func, std::size_t... I>
    inline static Value callFunction_r(lua_State *L, _Func&& _func, std::index_sequence<I...>)
    {
        const ValueType types[] { _types... };

        return std::forward<Value>((*_func)(std::forward<Value>(toValue(L, types[I], I + 1))...));
    }
};

}
}
