#pragma once

#include <unordered_set>

#include "PQLParserContext.h"
#include "qps/clause/Clause.h"

class BaseParserState : public IParserState {
 protected:
  static unordered_set<PQLTokenType> startTokensOfAvailClauses;
  static unordered_set<PQLTokenType> startTokensOfAvailClausesForSelect;
  PQLParserContext& parserContext;
  PQLTokenType prev;

 protected:
  explicit BaseParserState(PQLParserContext& parserContext, PQLTokenType prev);
  ~BaseParserState() override = default;
};
