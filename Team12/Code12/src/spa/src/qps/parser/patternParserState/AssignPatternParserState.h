#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "qps/argument/AbstractArgument.h"
#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"

using std::make_unique, std::unique_ptr;

class AssignPatternParserState : public BaseParserState {
 private:
  bool isInBracket;
  static const int FIRST_ARG = 0;
  static const int SECOND_ARG = 1;
  string matchPattern;
  int partialMatchWildCardCount;
  int argumentCount;
  unique_ptr<AbstractArgument> outerSynonym;
  static PredictiveMap predictiveMap;
  static PQLTokenType exitToken;
  static size_t maxNumberOfArgs;
  vector<unique_ptr<AbstractArgument>> patternArg;
  void processNameToken(PQLToken& curr) override;
  void processSynonymToken(PQLToken& curr);
  void processLastArgument();

 public:
  explicit AssignPatternParserState(PQLParserContext& parserContext);
  void handleToken() override;
  ~AssignPatternParserState() override = default;
};
