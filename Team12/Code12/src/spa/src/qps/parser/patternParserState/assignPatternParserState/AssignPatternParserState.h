#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "qps/argument/AbstractArgument.h"
#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"

class AssignPatternParserState : public BaseParserState {
 private:
  static const int FIRST_ARG = 0;
  static const int SECOND_ARG = 1;
  static const int PARTIAL_MATCH_COUNT = 2;
  static const int EXACT_MATCH_COUNT = 0;
  static const int WILDCARD_MATCH_COUNT = 1;
  static const size_t maxNumberOfArgs = 2;

  bool isInBracket;
  bool isPartialMatch;
  int secondArgWildcardCount;
  unique_ptr<AbstractArgument> synAssign;
  static PredictiveMap predictiveMap;
  static PQLTokenType exitToken;
  vector<unique_ptr<AbstractArgument>> patternArg;
  void processNameToken(PQLToken& curr) override;
  void processSynonymToken(PQLToken& curr);
  void processLastArgument();
  void checkIsValidIdent(const string& ref);
  static void checkIsValidExpr(const string& ref);

 public:
  explicit AssignPatternParserState(PQLParserContext& parserContext,
                                    PQLTokenType prev);
  void handleToken() override;
  ~AssignPatternParserState() override = default;
};
