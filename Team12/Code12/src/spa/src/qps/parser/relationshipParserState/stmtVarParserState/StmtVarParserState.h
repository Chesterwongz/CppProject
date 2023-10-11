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
  bool isSuccess;
  void checkIsValidSynonym(const string& synonym, int argumentNumber);
  void checkIsValidWildcard();
  static void checkIsValidIdent(const string& ref);

 public:
  explicit StmtVarParserState(PQLParserContext& parserContext,
                              string abstraction, PQLTokenType prev);
  void handleToken() override;
  ~StmtVarParserState() override = default;
};
