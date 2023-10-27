#include "Wildcard.h"

#include <iostream>

const string& Wildcard::getValue() { return wildcardValue; }

QPSStringUtils::ArgumentType Wildcard::getArgumentType() {
  return argumentType;
}

bool Wildcard::isWildcard() { return true; }

unique_ptr<AbstractArgument> Wildcard::clone() {
  return std::make_unique<Wildcard>(*this);
}

bool Wildcard::operator==(const AbstractArgument& other) const {
  const auto* otherWildcard = dynamic_cast<const Wildcard*>(&other);
  return otherWildcard;
}
