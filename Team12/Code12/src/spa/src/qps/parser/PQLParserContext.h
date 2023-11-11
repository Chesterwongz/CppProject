#pragma once

#include <memory>
#include <string>
#include <vector>

#include "IParserState.h"
#include "qps/clause/Clause.h"
#include "qps/common/PQLParserUtils.h"
#include "qps/exceptions/QPSSemanticError.h"
#include "qps/parser/synonymContext/SynonymContext.h"
#include "qps/parser/tokenizer/PQLTokenizer.h"
#include "qps/parser/tokenizer/token/PQLToken.h"
#include "qps/query/Query.h"

class PQLParserContext {
 private:
  unique_ptr<Query>& query;
  unique_ptr<SynonymContext> context;
  unique_ptr<PQLTokenStream> tokenStream;
  unique_ptr<IParserState> currState;
  bool isSemanticallyValid = true;

  //  handling of TokenStream
  static bool isExpectedToken(PQLTokenType curr, PQLTokenType prev,
                              PredictiveMap& pm);

 public:
  explicit PQLParserContext(unique_ptr<PQLTokenStream> tokenStream,
                            unique_ptr<Query>& query);

  //  Build clause - handling of Synonym Context
  void addToContext(string entity, const string& synonym);
  void addSelectClause();
  void addSelectClause(unique_ptr<SynonymArg> synonym);
  void addSelectClause(SynonymsToSelect synonyms);
  string getValidSynonymType(const string& synonym);
  bool checkSynonymExists(const string& synonym);

  //  Build clause - handling of query object
  void addNotClause(unique_ptr<NotDecorator> notClause);
  void addClause(unique_ptr<Clause> clause);
  void setSemanticallyInvalid();

  // handling of TokenStream
  std::optional<PQLToken> eatExpectedToken(PQLTokenType prev,
                                           PredictiveMap& pm);
  std::optional<PQLToken> eatCurrToken();
  std::optional<PQLToken> peekNextToken();

  // handling of parser state
  void transitionTo(unique_ptr<IParserState> nextState);
  void handleTokens();
};
