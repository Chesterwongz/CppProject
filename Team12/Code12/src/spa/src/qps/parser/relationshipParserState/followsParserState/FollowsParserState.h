#pragma once

#include <memory>
#include <vector>
#include <utility>

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/relationshipParserState/RelationshipParserState.h"

using std::make_unique, std::unique_ptr, std::vector;

class FollowsParserState : public RelationshipParserState {
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
  explicit FollowsParserState(PQLParserContext& parserContext);
  void handleToken() override;
  ~FollowsParserState() override = default;
};
