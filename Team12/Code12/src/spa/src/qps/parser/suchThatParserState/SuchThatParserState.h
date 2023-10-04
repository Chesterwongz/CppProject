#pragma once

#include <memory>

#include "qps/parser/IParserState.h"
#include "qps/parser/PQLParserContext.h"

// get such that and check next relation to determine relationship parser to use
class SuchThatParserState : public IParserState {
 private:
  PQLParserContext& parserContext;
  PQLTokenStream& tokenStream;
  PQLTokenType prev;
  static PredictiveMap predictiveMap;
  void processNameToken(PQLToken& curr) override;

 public:
  explicit SuchThatParserState(PQLParserContext& parserContext);
  void handleToken() override;
  ~SuchThatParserState() override = default;
};
