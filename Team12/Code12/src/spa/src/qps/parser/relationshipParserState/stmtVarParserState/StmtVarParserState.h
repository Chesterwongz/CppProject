#pragma once

#include "qps/parser/relationshipParserState/RelationshipParserState.h"

class StmtVarParserState : public RelationshipParserState {
 private:
  static unordered_map<string, Abstraction> stmtVarKeywordToAbstraction;
  static PredictiveMap predictiveMap;
  static const int FIRST_ARG = 0;
  static const int SECOND_ARG = 1;
  bool isSuccess;
  void checkIsValidSynonym(const string& synonym, int argumentNumber);
  void checkIsValidWildcard();
  static void checkIsValidIdent(const string& ref);

 public:
  explicit StmtVarParserState(PQLParserContext& parserContext);
  void handleToken() override;
  ~StmtVarParserState() override = default;
};
