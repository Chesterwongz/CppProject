#pragma once

#include <memory>

#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/clauseTransitionParserState/ClauseTransitionParserState.h"
#include "qps/parser/selectParserState/SelectTupleParsersState.h"

class SelectParserState : public BaseParserState {
 private:
  static PredictiveMap predictiveMap;

  void processNameToken(PQLToken& curr) override;

 public:
  explicit SelectParserState(PQLParserContext& parserContext,
                             PQLTokenType prev);
  void handleToken() override;
  ~SelectParserState() override = default;
};
