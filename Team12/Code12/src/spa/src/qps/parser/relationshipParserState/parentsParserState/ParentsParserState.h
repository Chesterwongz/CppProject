#pragma once

#include <memory>

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/relationshipParserState/RelationshipParserState.h"

using std::make_unique, std::unique_ptr;

class ParentsParserState : public RelationshipParserState {
 private:
  PQLParserContext& parserContext;
  PQLTokenStream& tokenStream;
  PQLTokenType prev;
  bool isTransitive;
  static PredictiveMap predictiveMap;
  static PQLTokenType exitToken;
  static size_t maxNumberOfArgs;
  void checkValidArgs(PQLToken& curr);

 public:
  explicit ParentsParserState(PQLParserContext& parserContext);
  void handleToken() override;
  ~ParentsParserState() override = default;
};
