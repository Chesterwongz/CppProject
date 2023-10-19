#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "qps/parser/relationshipParserState/RelationshipParserState.h"

class StmtVarParserState : public RelationshipParserState {
 private:
  static unordered_map<string, Abstraction> stmtVarKeywordToAbstraction;
  static PredictiveMap predictiveMap;
  string getIfValidSynonym(const string& synonym, size_t argumentNumber);
  void checkIsValidWildcard();

 public:
  explicit StmtVarParserState(PQLParserContext& parserContext,
                              string abstraction, PQLTokenType prev,
                              bool isNegated);
  void handleToken() override;
  ~StmtVarParserState() override = default;
};
