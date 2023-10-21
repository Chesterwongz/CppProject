#pragma once

#include <memory>
#include <string>

#include "qps/parser/BaseParserState.h"
#include "qps/parser/patternParserState/assignPatternParserState/AssignPatternParserState.h"
#include "qps/parser/patternParserState/ifPatternParserState/IfPatternParserState.h"
#include "qps/parser/patternParserState/whilePatternParserState/WhilePatternParserState.h"

// parses up to first argument of parser state
class PatternParserState : public BaseParserState {
 private:
  static PredictiveMap predictiveMap;
  void processNameToken(PQLToken& curr) override;
  void checkSafeExit();
  unique_ptr<SynonymArg> syn;
  vector<AbstractArgument> syn;
  bool isNegated = false;
  bool isInBracket = false;
  int numberOfArgs = 0;

 public:
  explicit PatternParserState(PQLParserContext& parserContext,
                              PQLTokenType prev);
  void handleToken() override;
  ~PatternParserState() override = default;
};
