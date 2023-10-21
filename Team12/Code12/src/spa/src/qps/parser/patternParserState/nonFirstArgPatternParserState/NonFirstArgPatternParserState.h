#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "qps/argument/AbstractArgument.h"
#include "qps/argument/patternExp/PatternExp.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/parser/BaseParserState.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/patternParserState/expressionParser/ExpressionValidator.h"

class NonFirstArgPatternParserState : public BaseParserState {
 private:

  bool isPartialMatch = false;
  static PredictiveMap predictiveMap;
  vector<unique_ptr<AbstractArgument>> secondPatternArg;
  static void checkIsValidExpr(const string& ref);
  void processWildcard(PQLTokenType prev);

 public:
  explicit NonFirstArgPatternParserState(PQLParserContext& parserContext,
                                    PQLTokenType prev);
  void handleToken() override;
  vector<unique_ptr<AbstractArgument>> getNonFirstArgs();
  bool getIsPartialMatch() const;
  ~NonFirstArgPatternParserState() override = default;
};
