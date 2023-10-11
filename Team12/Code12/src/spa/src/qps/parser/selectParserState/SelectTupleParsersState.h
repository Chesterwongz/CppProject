#pragma once

#include <memory>
#include <vector>

#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/clauseTransitionParserState/ClauseTransitionParserState.h"

class SelectTupleParsersState : public BaseParserState {
 private:
  static PredictiveMap predictiveMap;
  vector<unique_ptr<AbstractArgument>> synonymsToSelect;
  void processNameToken(PQLToken& curr) override;

 public:
  explicit SelectTupleParsersState(PQLParserContext& parserContext,
                                   PQLTokenType prev);

  void handleToken() override;
  ~SelectTupleParsersState() override = default;
};
