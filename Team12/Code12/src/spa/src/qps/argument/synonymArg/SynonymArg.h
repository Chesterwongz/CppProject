#pragma once

#include <string>

#include "qps/argument/AbstractArgument.h"

using std::string;

class SynonymArg : public AbstractArgument {
 private:
  const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::SYNONYM;
  string synonymValue;

 public:
  explicit SynonymArg(string argumentValue)
      : synonymValue(std::move(argumentValue)){};
  string getValue() override;
  QPSStringUtils::ArgumentType getArgumentType() override;
  bool isSynonym() override;
  bool operator==(const AbstractArgument& other) const override;
};
