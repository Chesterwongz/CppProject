#pragma once

#include <memory>
#include <utility>

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/relationshipParserState/RelationshipParserState.h"

using std::make_unique, std::unique_ptr;

class ModifiesParserState : public RelationshipParserState {
 private:
  PQLParserContext& parserContext;
  PQLTokenStream& tokenStream;
  PQLTokenType prev;
  static PredictiveMap predictiveMap;
  static PQLTokenType exitToken;
  static size_t maxNumberOfArgs;
  void checkValidSecondArg(PQLToken(&curr));

 public:
  explicit ModifiesParserState(PQLParserContext& parserContext);
  void handleToken() override;
  ~ModifiesParserState() override = default;
};
