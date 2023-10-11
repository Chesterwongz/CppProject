#include "PatternExp.h"

#include <string>

#include "qps/exceptions/QPSInvalidQueryException.h"

string PatternExp::getValue() { return patternExpValue; }

QPSStringUtils::ArgumentType PatternExp::getArgumentType() {
  return argumentType;
}

bool PatternExp::isPatternExp() { return true; }

bool PatternExp::operator==(const AbstractArgument& other) const {
  const auto* otherInteger = dynamic_cast<const PatternExp*>(&other);
  if (!otherInteger) return false;

  return this->patternExpValue == otherInteger->patternExpValue;
}
