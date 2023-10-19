#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "qps/argument/AbstractArgument.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/IfPatternClause.h"
#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/clauseTransitionParserState/ClauseTransitionParserState.h"
#include "qps/parser/patternParserState/expressionParser/ExpressionValidator.h"

class IfPatternParserState : public BaseParserState {
 private:
  static constexpr int expectedNumberOfArgs = 1;
  static constexpr int expectedNonFirstArgWildcardCount = 2;
  bool isNegated;
  unique_ptr<SynonymArg> synIf;
  static PredictiveMap predictiveMap;
  vector<unique_ptr<AbstractArgument>> patternArg;
  int nonFirstArgWildcardCount = 0;
  void processSynonymToken(PQLToken& curr);
  void checkSafeExit();

 public:
  explicit IfPatternParserState(PQLParserContext& parserContext,
                                PQLTokenType prev, unique_ptr<SynonymArg> synIf,
                                bool isNegated);
  void handleToken() override;
  ~IfPatternParserState() override = default;
};
