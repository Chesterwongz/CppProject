#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "qps/argument/AbstractArgument.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/WhilePatternClause.h"
#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/clauseTransitionParserState/ClauseTransitionParserState.h"
#include "qps/parser/patternParserState/expressionParser/ExpressionValidator.h"

class WhilePatternParserState : public BaseParserState {
 private:
  static constexpr int expectedNumberOfArgs = 1;
  static constexpr int expectedNonFirstArgWildcardCount = 1;
  bool isNegated;
  unique_ptr<SynonymArg> synWhile;
  static PredictiveMap predictiveMap;
  vector<unique_ptr<AbstractArgument>> patternArg;
  int nonFirstArgWildcardCount = 0;
  void processSynonymToken(PQLToken& curr);
  bool checkSafeExit();

 public:
  explicit WhilePatternParserState(PQLParserContext& parserContext,
                                   PQLTokenType prev,
                                   unique_ptr<SynonymArg> synWhile,
                                   bool isNegated);
  void handleToken() override;
  ~WhilePatternParserState() override = default;
};
