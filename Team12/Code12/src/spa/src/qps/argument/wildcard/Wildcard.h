#pragma once

#include <string>

#include "common/utils/StringUtils.h"
#include "qps/argument/AbstractArgument.h"
#include "qps/common/Keywords.h"

using std::string;

class Wildcard : public AbstractArgument {
 private:
  const QPSStringUtils::ArgumentType argumentType = QPSStringUtils::WILDCARD;
  string wildcardValue = WILDCARD_KEYWORD;

 public:
  explicit Wildcard() = default;
  string getValue() override;
  QPSStringUtils::ArgumentType getArgumentType() override;
  bool isWildcard() override;
  bool operator==(const AbstractArgument& other) const override;
};
