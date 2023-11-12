#pragma once

#include <string>

#include "common/utils/StringUtils.h"
#include "qps/common/QPSStringUtils.h"

using std::string;

class AbstractArgument {
 protected:
  static inline const string ARG_KEY_DELIMITER = "|";

 public:
  virtual const string& getValue() = 0;
  virtual QPSStringUtils::ArgumentType getArgumentType() = 0;
  virtual bool isIdent();
  virtual bool isInteger();
  virtual bool isSynonym() const;
  virtual bool isStmtSynonym();
  virtual bool isVarSynonym();
  virtual bool isProcSynonym();
  virtual bool isWildcard();
  virtual bool isPatternExp();
  virtual ~AbstractArgument() = default;
  virtual bool operator==(const AbstractArgument& other) const = 0;
  string getArgKey();
  virtual string getArgSignature();
};
