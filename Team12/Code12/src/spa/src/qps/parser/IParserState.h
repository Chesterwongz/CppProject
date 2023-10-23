#pragma once

#include "qps/exceptions/QPSSyntaxError.h"
#include "qps/parser/tokenizer/token/PQLToken.h"

class PQLParserContext;

enum class ClauseType {
  NULL_CLAUSE,
  SUCH_THAT_CLAUSE,
  PATTERN_CLAUSE,
  WITH_CLAUSE
};

class IParserState {
 protected:
  inline static ClauseType prevClauseType = ClauseType::NULL_CLAUSE;
  virtual void processNameToken(PQLToken& curr) = 0;

 public:
  virtual void handleToken() = 0;
  virtual ~IParserState() = default;
  friend class PQLParserContext;
};
