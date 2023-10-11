#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "qps/argument/ident/Ident.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/suchThatClause/SuchThatClause.h"
#include "qps/clause/utils/ClauseConstants.h"
#include "qps/parser/BaseParserState.h"
#include "qps/parser/clauseTransitionParserState/ClauseTransitionParserState.h"

class RelationshipParserState : public BaseParserState {
 protected:
  static constexpr size_t expectedNumberOfArgs = 2;

  bool isInBracket;
  ArgumentList arguments;
  string abstraction;
  virtual unique_ptr<SuchThatClause> createSuchThatClause(
      Abstraction abstractionEnum);
  static Abstraction getAbstractionType(
      const string &keyword,
      unordered_map<string, Abstraction> abstractionKeywordMap);
  explicit RelationshipParserState(PQLParserContext &parserContext,
                                   bool isInBracket, string abstraction,
                                   PQLTokenType prev);
  void processNameToken(PQLToken &curr) override;

 public:
  ~RelationshipParserState() override = default;
};
