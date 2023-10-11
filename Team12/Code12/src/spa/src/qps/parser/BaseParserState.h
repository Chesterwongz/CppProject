#pragma once

#include <unordered_set>

#include "PQLParserContext.h"
#include "qps/clause/Clause.h"

class BaseParserState : public IParserState {
 protected:
  static constexpr int FIRST_ARG = 0;
  static constexpr int SECOND_ARG = 1;
  static constexpr int THIRD_ARG = 2;
  PQLParserContext& parserContext;
  PQLTokenType prev;
  void processNameToken(PQLToken& curr) override;

  explicit BaseParserState(PQLParserContext& parserContext, PQLTokenType prev);
  ~BaseParserState() override = default;
};
