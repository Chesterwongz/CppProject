#include "Integer.h"

#include <string>

#include "qps/exceptions/QPSInvalidQueryException.h"

const string& Integer::getValue() { return integerValue; }

QPSStringUtils::ArgumentType Integer::getArgumentType() { return argumentType; }

bool Integer::isInteger() { return true; }

unique_ptr<AbstractArgument> Integer::clone() {
  return std::make_unique<Integer>(*this);
}

bool Integer::operator==(const AbstractArgument& other) const {
  const auto* otherInteger = dynamic_cast<const Integer*>(&other);
  if (!otherInteger) return false;

  return this->integerValue == otherInteger->integerValue;
}
