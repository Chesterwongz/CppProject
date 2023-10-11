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

class AssignPatternParserState : public BaseParserState {
 private:
  static constexpr int PARTIAL_MATCH_COUNT = 2;
  static constexpr int EXACT_MATCH_COUNT = 0;
  static constexpr int WILDCARD_MATCH_COUNT = 1;
  static constexpr size_t expectedNumberOfArgs = 2;

  bool isPartialMatch;
  int secondArgWildcardCount;
  unique_ptr<SynonymArg> synAssign;
  static PredictiveMap predictiveMap;
  vector<unique_ptr<AbstractArgument>> patternArg;
  void processSynonymToken(PQLToken& curr);
  void processLastArgument();
  bool checkSafeExit();
  void checkIsValidIdent(const string& ref);
  static void checkIsValidExpr(const string& ref);

 public:
  explicit AssignPatternParserState(PQLParserContext& parserContext,
                                    PQLTokenType prev,
                                    unique_ptr<SynonymArg> synAssign);
  void handleToken() override;
  ~AssignPatternParserState() override = default;
};
