#include "PatternExp.h"

#include <string>

#include "qps/exceptions/QPSInvalidQueryException.h"

PatternExp::PatternExp(string argumentValue) {
  patternExpValue = QPSStringUtils::convertToRPN(argumentValue);
}

const string& PatternExp::getValue() { return patternExpValue; }

QPSStringUtils::ArgumentType PatternExp::getArgumentType() {
  return argumentType;
}

bool PatternExp::isPatternExp() { return true; }

unique_ptr<AbstractArgument> PatternExp::clone() {
  return std::make_unique<PatternExp>(*this);
}

bool PatternExp::operator==(const AbstractArgument& other) const {
  const auto* otherPatternExp = dynamic_cast<const PatternExp*>(&other);
  if (!otherPatternExp) return false;

  return this->patternExpValue == otherPatternExp->patternExpValue;
}
