#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/parser/BaseParserState.h"
#include "qps/parser/clauseTransitionParserState/ClauseTransitionParserState.h"
#include "qps/clause/patternClause/AssignPatternClause.h"
#include "qps/clause/patternClause/IfPatternClause.h"
#include "qps/clause/patternClause/WhilePatternClause.h"
#include "qps/parser/patternParserState/nonFirstArgPatternParserState/NonFirstArgPatternParserState.h"

// parses up to first argument of parser state
class PatternParserState : public BaseParserState {
 private:
  enum PatternState {
    IF_PATTERN,
    ASSIGN_WHILE_PATTERN,
    INVALID_PATTERN
  };
  static PredictiveMap predictiveMap;
  static const size_t IF_ARG_COUNT = 2;
  static const size_t ASSIGN_WHILE_ARG_COUNT = 1;

  void processNameToken(PQLToken& curr) override;
  void checkSafeExit();
  void createPatternClause();
  unique_ptr<SynonymArg> syn;
  unique_ptr<AbstractArgument> firstArg;
  vector<unique_ptr<AbstractArgument>> nonFirstArgs;
  PatternState parsedPatternState = INVALID_PATTERN;
  bool isNegated = false;
  bool isInBracket = false;
  bool isPartialMatch = false;

 public:
  explicit PatternParserState(PQLParserContext& parserContext,
                              PQLTokenType prev);
  void handleToken() override;
  ~PatternParserState() override = default;
};
