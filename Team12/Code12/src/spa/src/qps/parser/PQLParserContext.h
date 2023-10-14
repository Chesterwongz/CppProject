#pragma once

#include <memory>
#include <string>
#include <vector>

#include "IParserState.h"
#include "qps/clause/Clause.h"
#include "qps/common/PQLParserUtils.h"
#include "qps/context/Context.h"
#include "qps/query/Query.h"
#include "qps/tokenizer/PQLTokenizer.h"

class PQLParserContext {
 private:
  // TODO(Koon Hwee): After Select Clause is implemented,
  //  PQLParserContext should not be a decorator, should
  //  directly return Query object
  unique_ptr<Query>& query;
  unique_ptr<Context> context;
  unique_ptr<PQLTokenStream> tokenStream;
  unique_ptr<IParserState> currState;

  //  handling of TokenStream
  static bool isExpectedToken(PQLTokenType curr, PQLTokenType prev,
                              PredictiveMap& pm);

 public:
  explicit PQLParserContext(unique_ptr<PQLTokenStream> tokenStream,
                            unique_ptr<Query>& query);

  //  Build clause - handling of Synonym Context
  void addToContext(string entity, const string& synonym);
  void addSelectClause(const string& synonym);
  void addSelectClause(SynonymsToSelect synonyms);
  string getValidSynonymType(const string& synonym);
  bool checkSynonymExists(const string& synonym);

  //  Build clause - handling of query object
  void addClause(unique_ptr<Clause> clause);

  // handling of TokenStream
  std::optional<PQLToken> eatExpectedToken(PQLTokenType prev,
                                           PredictiveMap& pm);
  std::optional<PQLToken> eatCurrToken();

  // handling of parser state
  void transitionTo(unique_ptr<IParserState> nextState);
  void handleTokens();
};
