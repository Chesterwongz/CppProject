#pragma once

#include <memory>

#include "qps/parser/IParserState.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/patternParserState/PatternParserState.h"
#include "qps/parser/suchThatParserState/SuchThatParserState.h"
#include "qps/parser/withParserState/WithParserState.h"

class ClauseTransitionParserState : public IParserState {
 private:
  static PredictiveMap predictiveMap;
  void processNameToken(PQLToken& curr) override;
  PQLParserContext& parserContext;

 public:
  void handleToken() override;
  static void setClauseTransitionState(PQLParserContext& pc);
  void createAndClause(PQLParserContext& pc);
  explicit ClauseTransitionParserState(PQLParserContext& parserContext);
  ~ClauseTransitionParserState() override = default;
};
