#pragma once

#include "qps/parser/BaseParserState.h"

class PatternParsersState : public BaseParserState {
 private:
  static PredictiveMap predictiveMap;
  void processNameToken(PQLToken& curr) override;
  void processSynonymToken(PQLToken& curr);

 public:
  explicit PatternParsersState(PQLParserContext& parserContext);
  void handleToken() override;
  ~PatternParsersState() override = default;
};
