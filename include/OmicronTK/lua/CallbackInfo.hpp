#pragma once

#include "OmicronTK/lua/defines.hpp"
#include <OmicronTK/lua/util/ObjectUtil.hpp>
#include <OmicronTK/lua/Value.hpp>

#include <lua.hpp>

namespace OmicronTK {
namespace lua {

class CallbackInfo
{
public:
    class ReturnValue
    {
        ReturnValue(lua_State *L);

    public:
        inline int length() const { return m_length; }

        void add(const Value &value);

    private:
        lua_State *m_state;
        int m_length;

        friend class CallbackInfo;
    };

    explicit CallbackInfo(lua_State *L);
    ~CallbackInfo();

    inline lua_State *state() const { return m_state; }

    inline int length() const { return m_length; }

    double getNumber(int idx, bool required = false, double defaultValue = 0.0) const;
    float getFloat(int idx, bool required = false, float defaultValue = 0.0f) const;
    int getInteger(int idx, bool required = false, int defaultValue = 0) const;
    unsigned int getUInt(int idx, bool required = false, unsigned int defaultValue = 0u) const;
    long getLong(int idx, bool required = false, long defaultValue = 0L) const;
    unsigned long getULong(int idx, bool required = false, unsigned long defaultValue = 0UL) const;
    const char *getCString(int idx, bool required = false, const char *defaultValue = "") const;
    std::string getString(int idx, bool required = false, std::string defaultValue = std::string()) const;
    lua_CFunction getCFunction(int idx, bool required = false, lua_CFunction defaultValue = nullptr) const;
    bool getBoolean(int idx, bool required = false, bool defaultValue = false) const;
    void *getUserData(int idx, bool required = false, void *defaultValue = nullptr) const;
    void *getLightUserData(int idx, bool required = false, void *defaultValue = nullptr) const;

    inline ReturnValue &getReturnValue() { return m_returnValue; }

    template<typename T>
    inline T *getUserData(int idx) const
    {
        return static_cast<T *>(getUserData(idx));
    }

    template<typename T>
    inline T *getLightUserData(int idx) const
    {
        return static_cast<T *>(getLightUserData(idx));
    }

    template<typename T = void>
    inline void newUserData(int idx, const char *className, T *userdata) const
    {
        *static_cast<void **>(lua_newuserdata(m_state, sizeof(T *))) = userdata;

        luaL_setmetatable(m_state, className);
        lua_setfield(m_state, idx, "__userdata");
    }

    template<typename T = void>
    inline T *checkUserData(int idx, const char *className) const
    {
        luaL_checktype(m_state, idx, LUA_TTABLE);
        lua_getfield(m_state, idx, "__userdata");

        return *static_cast<T **>(luaL_checkudata(m_state, -1, className));
    }

    template<typename... Args>
    inline int error(const char *fmt, Args... args) const
    {
        return luaL_error(m_state, fmt, args...);
    }

private:
    lua_State *m_state;
    const int m_length;
    ReturnValue m_returnValue;
};

using LuaCppFunction = int (CallbackInfo &info);

}
}
