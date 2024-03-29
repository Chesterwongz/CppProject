#pragma once

#include <memory>
#include <utility>

#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/clauseTransitionParserState/ClauseTransitionParserState.h"
#include "qps/parser/selectParserState/SelectTupleParsersState.h"

class SelectParserState : public BaseParserState {
 private:
  static PredictiveMap predictiveMap;

 public:
  void processNameToken(PQLToken& curr) override;
  explicit SelectParserState(PQLParserContext& parserContext,
                             PQLTokenType prev);
  void handleToken() override;
  ~SelectParserState() override = default;
};
