#pragma once

#include <string>
#include <utility>

#include "qps/argument/AbstractArgument.h"
#include "qps/parser/tokenizer/token/PQLToken.h"

using std::string;

class Ident : public AbstractArgument {
 private:
  const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::IDENT;
  string identValue;

 public:
  explicit Ident(string argumentValue) : identValue(std::move(argumentValue)) {}
  const string& getValue() override;
  QPSStringUtils::ArgumentType getArgumentType() override;
  bool isIdent() override;
  bool operator==(const AbstractArgument& other) const override;
};
