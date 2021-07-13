#pragma once

#include "OmicronTK/lua/defines.hpp"
#include <OmicronTK/lua/Value.hpp>

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
        void pushValue(int idx);

    private:
        lua_State *m_state;
        int m_length;

        friend class CallbackInfo;
    };

    explicit CallbackInfo(lua_State *L);
    ~CallbackInfo();

    inline int length() const { return m_length; }
    inline lua_State *state() const { return m_state; }
    inline ReturnValue &getReturnValue() { return m_returnValue; }

    void required(int value) const;
    void required(int min, int max) const;

    int error(const char *message) const;

    double getNumber(int idx, double defaultValue = 0.0) const;
    float getFloat(int idx, float defaultValue = 0.0f) const;
    int getInteger(int idx, int defaultValue = 0) const;
    unsigned int getUInt(int idx, unsigned int defaultValue = 0u) const;
    long getLong(int idx, long defaultValue = 0L) const;
    unsigned long getULong(int idx, unsigned long defaultValue = 0UL) const;
    const char *getCString(int idx, const char *defaultValue = "") const;
    std::string getString(int idx, const std::string &defaultValue = std::string()) const;
    LuaCFunction getCFunction(int idx, LuaCFunction defaultValue = nullptr) const;
    bool getBoolean(int idx, bool defaultValue = false) const;
    void *getLightUserData(int idx, void *defaultValue = nullptr) const;
    void *getUserData(int idx, void *defaultValue = nullptr) const;

    void *checkUserData(int idx, const char *className) const;
    void newUserData(int idx, const char *className, void *userdata) const;

    template<typename T>
    inline T *getLightUserData(int idx) const
    {
        return static_cast<T *>(getLightUserData(idx));
    }

    template<typename T>
    inline T *getUserData(int idx) const
    {
        return static_cast<T *>(getUserData(idx));
    }

    template<typename T>
    inline T *checkUserData(int idx, const char *className) const
    {
        return static_cast<T *>(checkUserData(idx, className));
    }

private:
    lua_State *m_state;
    const int m_length;
    ReturnValue m_returnValue;
};

using LuaCppFunction = int (CallbackInfo &info);

}
}
