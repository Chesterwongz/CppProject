#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/clauseTransitionParserState/ClauseTransitionParserState.h"
#include "qps/parser/relationshipParserState/RelationshipParserState.h"

class StmtStmtParserState : public RelationshipParserState {
 private:
  static unordered_map<string, Abstraction> stmtStmtKeywordToAbstraction;
  static PredictiveMap predictiveMap;
  string checkIsStmtSynonym(const string& synonym);

 public:
  explicit StmtStmtParserState(PQLParserContext& parserContext,
                               string abstraction, PQLTokenType prev,
                               bool isNegated);
  void handleToken() override;
  ~StmtStmtParserState() override = default;
};
