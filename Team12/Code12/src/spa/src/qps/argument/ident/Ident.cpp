#include "Ident.h"

#include "qps/exceptions/QPSInvalidQueryException.h"

const string& Ident::getValue() { return identValue; }

QPSStringUtils::ArgumentType Ident::getArgumentType() { return argumentType; }

bool Ident::isIdent() { return true; }

unique_ptr<AbstractArgument> Ident::clone() {
  return std::make_unique<Ident>(*this);
}

bool Ident::operator==(const AbstractArgument& other) const {
  const auto* otherIdent = dynamic_cast<const Ident*>(&other);
  if (!otherIdent) return false;

  return this->identValue == otherIdent->identValue;
}
