#pragma once

#include <memory>

#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/patternParserState/PatternParserState.h"
#include "qps/parser/selectParserState/SelectTupleParsersState.h"
#include "qps/parser/suchThatParserState/SuchThatParserState.h"

class SelectParserState : public BaseParserState {
 private:
  static PredictiveMap predictiveMap;
  static PQLTokenType exitToken;

  void processNameToken(PQLToken& curr) override;

 public:
  explicit SelectParserState(PQLParserContext& parserContext,
                             PQLTokenType prev);
  void handleToken() override;
  ~SelectParserState() override = default;
};
