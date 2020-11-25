#include "ValuePrivateBase.hpp"

#include <string>

namespace OmicronTK {
namespace lua {

Value::Type ValuePrivateBase::type() const { return Value::Nil; }

double ValuePrivateBase::number_value() const { return 0.0; }

int ValuePrivateBase::integer_value() const { return 0; }

const std::string &ValuePrivateBase::string_value() const { return EmptyString; }

LuaCFunction ValuePrivateBase::cfunction_value() const { return nullptr; }

bool ValuePrivateBase::boolean_value() const { return false; }

void *ValuePrivateBase::userdata_value() const { return nullptr; }

}
}
