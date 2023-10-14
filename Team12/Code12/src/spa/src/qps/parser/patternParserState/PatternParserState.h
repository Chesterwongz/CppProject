#pragma once

#include <memory>
#include <string>

#include "qps/parser/BaseParserState.h"
#include "qps/parser/patternParserState/assignPatternParserState/AssignPatternParserState.h"
#include "qps/parser/patternParserState/ifPatternParserState/IfPatternParserState.h"
#include "qps/parser/patternParserState/whilePatternParserState/WhilePatternParserState.h"

class PatternParserState : public BaseParserState {
 private:
  static PredictiveMap predictiveMap;
  void processNameToken(PQLToken& curr) override;
  void processSynonymToken(PQLToken& curr);

 public:
  explicit PatternParserState(PQLParserContext& parserContext,
                              PQLTokenType prev);
  void handleToken() override;
  ~PatternParserState() override = default;
};
