#include "OmicronTK/lua/LuaValue.hpp"
#include "private/LuaValueBase.hpp"
#include "OmicronTK/lua/defines.hpp"

#include <string>

namespace OmicronTK {
namespace lua {

class LuaNil : public Value<LuaValue::Nil, void *>
{
public:
    LuaNil() : Value(nullptr) {}
};

class LuaNumber : public Value<LuaValue::Number, double>
{
public:
    LuaNumber(double value) : Value(value) {}
    double number_value() const override { return m_value; }
};

class LuaInteger : public Value<LuaValue::Integer, int>
{
public:
    LuaInteger(int value) : Value(value) {}
    int integer_value() const override { return m_value; }
};

class LuaString : public Value<LuaValue::String, std::string>
{
public:
    LuaString(const std::string &value) : Value(value) {}

    const std::string &string_value() const override { return m_value; }
};

class LuaClosure : public Value<LuaValue::CFunction, LuaCFunction>
{
public:
    LuaClosure(LuaCFunction value) : Value(value) {}
    LuaCFunction cfunction_value() const override { return m_value; }
};

class LuaBoolean : public Value<LuaValue::Boolean, bool>
{
public:
    LuaBoolean(bool value) : Value(value) {}
    bool boolean_value() const override { return m_value; }
};

class LuaUserData : public Value<LuaValue::UserData, void *>
{
public:
    LuaUserData(void *value) : Value(value) {}
    void *userdata_value() const override { return m_value; }
};

LuaValue::LuaValue() : m_ptr(std::make_shared<LuaNil>()) {}
LuaValue::LuaValue(double value) : m_ptr(std::make_shared<LuaNumber>(value)) {}
LuaValue::LuaValue(int value) : m_ptr(std::make_shared<LuaInteger>(value)) {}
LuaValue::LuaValue(const char *value) : m_ptr(std::make_shared<LuaString>(value)) {}
LuaValue::LuaValue(const std::string &value) : m_ptr(std::make_shared<LuaString>(value)) {}
LuaValue::LuaValue(LuaCFunction value) : m_ptr(std::make_shared<LuaClosure>(value)) {}
LuaValue::LuaValue(LuaCppFunction value) : m_ptr(std::make_shared<LuaClosure>(reinterpret_cast<LuaCFunction>(value))) {}
LuaValue::LuaValue(bool value) : m_ptr(std::make_shared<LuaBoolean>(value)) {}
LuaValue::LuaValue(void *value) : m_ptr(std::make_shared<LuaUserData>(value)) {}

LuaValue::Type LuaValue::type() const { return m_ptr->type(); }

void *LuaValue::nil_value() const { return nullptr; }
double LuaValue::number_value() const { return m_ptr->number_value(); }
int LuaValue::integer_value() const { return m_ptr->integer_value(); }
const std::string &LuaValue::string_value() const { return m_ptr->string_value(); }
LuaCFunction LuaValue::cfunction_value() const { return m_ptr->cfunction_value(); }
bool LuaValue::boolean_value() const { return m_ptr->boolean_value(); }
void *LuaValue::userdata_value() const { return m_ptr->userdata_value(); }

}
}
