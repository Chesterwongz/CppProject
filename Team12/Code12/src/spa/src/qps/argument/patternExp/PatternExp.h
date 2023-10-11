#pragma once

#include <string>
#include <utility>

#include "qps/argument/AbstractArgument.h"

using std::string;

class PatternExp : public AbstractArgument {
 private:
  const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::PATTERNEXP;
  string patternExpValue;

 public:
  explicit PatternExp(string argumentValue)
      : patternExpValue(std::move(argumentValue)) {}
  string getValue() override;
  QPSStringUtils::ArgumentType getArgumentType() override;
  bool isPatternExp() override;
  bool operator==(const AbstractArgument& other) const override;
};
