#pragma once

#include <unordered_set>

#include "IParserState.h"
#include "PQLParserContext.h"
#include "qps/clause/Clause.h"

class BaseParserState : public IParserState {
 protected:
  static unordered_set<PQLTokenType> startTokensOfAvailClauses;
  PQLParserContext& parserContext;
  PQLTokenStream& tokenStream;
  PQLTokenType prev;

 protected:
  explicit BaseParserState(PQLParserContext& parserContext);
  ~BaseParserState() override = default;
};
