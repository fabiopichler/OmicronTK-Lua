#pragma once

#include "OmicronTK/lua/defines.hpp"
#include <OmicronTK/lua/util/ObjectUtil.hpp>

#include <lua.hpp>

namespace OmicronTK {
namespace lua {

class CallbackInfo
{
public:
    CallbackInfo(lua_State *L);

    inline lua_State *state() { return m_state; }

    int length();

    double getNumber(int idx);
    float getFloat(int idx);
    int getInteger(int idx);
    unsigned int getUInt(int idx);
    long getLong(int idx);
    unsigned long getULong(int idx);
    const char *getCString(int idx);
    std::string getString(int idx);
    lua_CFunction getCFunction(int idx);
    bool getBoolean(int idx);
    void *getUserData(int idx);
    void *getLightUserData(int idx);

    template<typename T>
    inline T *getUserData(int idx)
    {
        return static_cast<T *>(getUserData(idx));
    }

    template<typename T>
    inline T *getLightUserData(int idx)
    {
        return static_cast<T *>(getLightUserData(idx));
    }

    template<typename T = void>
    inline void newUserData(int idx, const char *className, T *userdata)
    {
        *static_cast<void **>(lua_newuserdata(m_state, sizeof(T *))) = userdata;

        luaL_setmetatable(m_state, className);
        lua_setfield(m_state, idx, "__userdata");
    }

    template<typename T = void>
    inline T *checkUserData(int idx, const char *className)
    {
        luaL_checktype(m_state, idx, LUA_TTABLE);
        lua_getfield(m_state, idx, "__userdata");

        return *static_cast<T **>(luaL_checkudata(m_state, -1, className));
    }

    template<typename... Args>
    inline int error(const char *fmt, Args... args)
    {
        return luaL_error(m_state, fmt, args...);
    }

private:
    lua_State *m_state;
};

using LuaCppFunction = int (*)(CallbackInfo info);

}
}
