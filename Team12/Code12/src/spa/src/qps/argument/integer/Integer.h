#pragma once

#include <string>

#include "qps/argument/AbstractArgument.h"

using std::string;

class Integer : public AbstractArgument {
 private:
  const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::INTEGER;
  string integerValue;

 public:
  explicit Integer(string argumentValue)
      : integerValue(std::move(argumentValue)){};
  string getValue() override;
  QPSStringUtils::ArgumentType getArgumentType() override;
  bool isInteger() override;
  virtual bool operator==(const AbstractArgument& other) const override;
};
