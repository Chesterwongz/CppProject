#pragma once

#include <memory>

#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"

class DeclarativeParserState : public BaseParserState {
 private:
  string currentEntity;
  static PredictiveMap predictiveMap;
  void processNameToken(PQLToken& curr) override;

 public:
  explicit DeclarativeParserState(PQLParserContext& parserContext);
  void handleToken() override;
  ~DeclarativeParserState() override = default;
};
