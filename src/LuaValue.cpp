#include "OmicronTK/lua/LuaValue.hpp"
#include "private/LuaValueBase.hpp"
#include "OmicronTK/lua/defines.hpp"

#include <string>

namespace OmicronTK {
namespace lua {

class LuaNumber : public Value<double>
{
public:
    LuaNumber(double value) : Value(value, LuaValueType::Number) {}
    double number_value() const override { return m_value; }
};

class LuaInteger : public Value<int>
{
public:
    LuaInteger(int value) : Value(value, LuaValueType::Integer) {}
    int integer_value() const override { return m_value; }
};

class LuaString : public Value<std::string>
{
public:
    LuaString(const std::string &value) : Value(value, LuaValueType::String) {}

    const std::string &string_value() const override { return m_value; }
};

class LuaClosure : public Value<LuaCFunction>
{
public:
    LuaClosure(LuaCFunction value) : Value(value, LuaValueType::CFunction) {}
    LuaCFunction cfunction_value() const override { return m_value; }
};

class LuaBoolean : public Value<bool>
{
public:
    LuaBoolean(bool value) : Value(value, LuaValueType::Boolean) {}
    bool boolean_value() const override { return m_value; }
};

class LuaLightuserdata : public Value<void *>
{
public:
    LuaLightuserdata(void *value) : Value(value, LuaValueType::Lightuserdata) {}
    void *lightuserdata_value() const override { return m_value; }
};

LuaValue::LuaValue(double value) : m_ptr(std::make_shared<LuaNumber>(value)) {}
LuaValue::LuaValue(int value) : m_ptr(std::make_shared<LuaInteger>(value)) {}
LuaValue::LuaValue(const char *value) : m_ptr(std::make_shared<LuaString>(value)) {}
LuaValue::LuaValue(const std::string &value) : m_ptr(std::make_shared<LuaString>(value)) {}
LuaValue::LuaValue(LuaCFunction value) : m_ptr(std::make_shared<LuaClosure>(value)) {}
LuaValue::LuaValue(LuaCppFunction value) : m_ptr(std::make_shared<LuaClosure>(reinterpret_cast<LuaCFunction>(value))) {}
LuaValue::LuaValue(bool value) : m_ptr(std::make_shared<LuaBoolean>(value)) {}
LuaValue::LuaValue(void *value) : m_ptr(std::make_shared<LuaLightuserdata>(value)) {}

LuaValueType LuaValue::type() const { return m_ptr->type(); }
double LuaValue::number_value() const { return m_ptr->number_value(); }
int LuaValue::integer_value() const { return m_ptr->integer_value(); }
const std::string &LuaValue::string_value() const { return m_ptr->string_value(); }
LuaCFunction LuaValue::cfunction_value() const { return m_ptr->cfunction_value(); }
bool LuaValue::boolean_value() const { return m_ptr->boolean_value(); }
void *LuaValue::lightuserdata_value() const { return m_ptr->lightuserdata_value(); }

}
}
