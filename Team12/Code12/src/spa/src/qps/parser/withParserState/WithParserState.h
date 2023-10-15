#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "qps/argument/AbstractArgument.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"

class WithParserState : public BaseParserState {
 private:
  static PredictiveMap predictiveMap;
  static const int expectedNumberOfArgs = 2;
  vector<unique_ptr<AbstractArgument>> arguments;
  vector<ArgumentType> argumentTypes;
  void checkSameTypeComparison();

 public:
  explicit WithParserState(PQLParserContext& parserContext, PQLTokenType prev);
  void handleToken() override;
  ~WithParserState() override = default;
};
