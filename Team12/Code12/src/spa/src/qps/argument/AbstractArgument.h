#pragma once

#include <string>

#include "common/utils/StringUtils.h"
#include "qps/common/QPSStringUtils.h"

using std::string

class AbstractArgument {
 public:
  virtual const string& getValue() = 0;
  virtual QPSStringUtils::ArgumentType getArgumentType() = 0;
  virtual bool isIdent();
  virtual bool isInteger();
  virtual bool isSynonym();
  virtual bool isStmtSynonym();
  virtual bool isVarSynonym();
  virtual bool isProcSynonym();
  virtual bool isWildcard();
  virtual bool isPatternExp();
  virtual ~AbstractArgument() = default;
  virtual bool operator==(const AbstractArgument& other) const = 0;
};
