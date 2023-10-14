#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "qps/parser/PQLParserContext.h"
#include "qps/parser/relationshipParserState/RelationshipParserState.h"

class ProcProcParserState : public RelationshipParserState {
 private:
  static unordered_map<string, Abstraction> procProcKeywordToAbstraction;
  static PredictiveMap predictiveMap;
  void checkIsProcSynonym(const string& synonym);

 public:
  explicit ProcProcParserState(PQLParserContext& parserContext,
                               string abstraction, PQLTokenType prev);
  void handleToken() override;
  ~ProcProcParserState() override = default;
};
