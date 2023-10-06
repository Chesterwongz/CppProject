#pragma once

#include "qps/parser/BaseParserState.h"

class PatternParserState : public BaseParserState {
 private:
  static PredictiveMap predictiveMap;
  void processNameToken(PQLToken& curr) override;
  void processSynonymToken(PQLToken& curr);

 public:
  explicit PatternParserState(PQLParserContext& parserContext);
  void handleToken() override;
  ~PatternParserState() override = default;
};
