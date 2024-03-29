#pragma once

#include <memory>
#include <utility>

#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"

// get such that and check next relation to determine relationship parser to use
class SuchThatParserState : public BaseParserState {
 private:
  static PredictiveMap predictiveMap;
  void processNameToken(PQLToken& curr) override;
  bool isNegated = false;

 public:
  explicit SuchThatParserState(PQLParserContext& parserContext,
                               PQLTokenType prev);
  void handleToken() override;
  ~SuchThatParserState() override = default;
};
