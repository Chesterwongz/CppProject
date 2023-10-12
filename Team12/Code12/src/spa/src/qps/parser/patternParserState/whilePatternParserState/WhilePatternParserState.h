#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "qps/argument/AbstractArgument.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/PatternClause.h"
#include "qps/exceptions/QPSParserError.h"
#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/clauseTransitionParserState/ClauseTransitionParserState.h"
#include "qps/parser/patternParserState/expressionParser/ExpressionValidator.h"

class WhilePatternParserState : public BaseParserState {
 private:
  static constexpr int expectedNumberOfArgs = 2;
  static constexpr int expectedNonFirstArgWildcardCount = 1;
  unique_ptr<SynonymArg> synWhile;
  static PredictiveMap predictiveMap;
  vector<unique_ptr<AbstractArgument>> patternArg;
  int nonFirstArgWildcardCount;
  void processSynonymToken(PQLToken& curr);
  bool checkSafeExit();

 public:
  explicit WhilePatternParserState(PQLParserContext& parserContext,
                                   PQLTokenType prev,
                                   unique_ptr<SynonymArg> synWhile);
  void handleToken() override;
  ~WhilePatternParserState() override = default;
};
