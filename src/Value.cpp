#include "OmicronTK/lua/Value.hpp"
#include "private/ValuePrivateBase.hpp"
#include "OmicronTK/lua/defines.hpp"

#include <string>

namespace OmicronTK {
namespace lua {

class LuaNil : public ValuePrivate<Value::Nil, void *>
{
public:
    LuaNil() : ValuePrivate(nullptr) {}
};

class LuaNumber : public ValuePrivate<Value::Number, double>
{
public:
    LuaNumber(double value) : ValuePrivate(value) {}
    double number_value() const override { return m_value; }
};

class LuaInteger : public ValuePrivate<Value::Integer, int>
{
public:
    LuaInteger(int value) : ValuePrivate(value) {}
    int integer_value() const override { return m_value; }
};

class LuaString : public ValuePrivate<Value::String, std::string>
{
public:
    LuaString(const std::string &value) : ValuePrivate(value) {}

    const std::string &string_value() const override { return m_value; }
};

class LuaClosure : public ValuePrivate<Value::CFunction, LuaCFunction>
{
public:
    LuaClosure(LuaCFunction value) : ValuePrivate(value) {}
    LuaCFunction cfunction_value() const override { return m_value; }
};

class LuaBoolean : public ValuePrivate<Value::Boolean, bool>
{
public:
    LuaBoolean(bool value) : ValuePrivate(value) {}
    bool boolean_value() const override { return m_value; }
};

class LuaUserData : public ValuePrivate<Value::UserData, void *>
{
public:
    LuaUserData(void *value) : ValuePrivate(value) {}
    void *userdata_value() const override { return m_value; }
};

// test
Value::Value(unsigned int value) : m_ptr(std::make_shared<LuaInteger>(value)) {}

Value::Value(Value &&value) : m_ptr(value.m_ptr) {}
Value::Value(const Value &value) : m_ptr(value.m_ptr) {}
Value::Value() : m_ptr(std::make_shared<LuaNil>()) {}
Value::Value(double value) : m_ptr(std::make_shared<LuaNumber>(value)) {}
Value::Value(int value) : m_ptr(std::make_shared<LuaInteger>(value)) {}
Value::Value(const char *value) : m_ptr(std::make_shared<LuaString>(value)) {}
Value::Value(const std::string &value) : m_ptr(std::make_shared<LuaString>(value)) {}
Value::Value(LuaCFunction value) : m_ptr(std::make_shared<LuaClosure>(value)) {}
Value::Value(LuaCppFunction value) : m_ptr(std::make_shared<LuaClosure>(reinterpret_cast<LuaCFunction>(value))) {}
Value::Value(bool value) : m_ptr(std::make_shared<LuaBoolean>(value)) {}
Value::Value(void *value) : m_ptr(std::make_shared<LuaUserData>(value)) {}

Value::Type Value::type() const { return m_ptr->type(); }

void *Value::nil_value() const { return nullptr; }
double Value::number_value() const { return m_ptr->number_value(); }
int Value::integer_value() const { return m_ptr->integer_value(); }
const std::string &Value::string_value() const { return m_ptr->string_value(); }
LuaCFunction Value::cfunction_value() const { return m_ptr->cfunction_value(); }
bool Value::boolean_value() const { return m_ptr->boolean_value(); }
void *Value::userdata_value() const { return m_ptr->userdata_value(); }

}
}
