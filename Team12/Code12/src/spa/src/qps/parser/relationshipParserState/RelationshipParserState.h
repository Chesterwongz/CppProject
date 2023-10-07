#pragma once

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
#include "qps/parser/patternParserState/PatternParserState.h"

class RelationshipParserState : public BaseParserState {
 protected:
  static int expectedNumberOfArgs;
  bool isInBracket;
  ArgumentList arguments;
  string relationship;
  virtual bool checkSafeExit(ArgumentList &arguments);
  Abstraction getAbstractionType(
      const string &keyword,
      unordered_map<string, Abstraction> abstractionKeywordMap);
  explicit RelationshipParserState(PQLParserContext &parserContext,
                                   bool isInBracket);
  void processNameToken(PQLToken &curr) override;

 public:
  ~RelationshipParserState() override = default;
};
