#include "QPS.h"

QPS::QPS(PKBReader& pkb) : pkb(pkb), tokenizerFactory() {}

std::set<string> QPS::processQueryString(const string& query) {
  unique_ptr<PQLTokenizer> tokenizer = tokenizerFactory.makeTokenizer(query);
  unique_ptr<PQLTokenList> tokenList = tokenizer->tokenize();
  PQLTokenStream tokenStream(*tokenList);

  Query queryObj(pkb);

  PQLParserContext parserContext(tokenStream, queryObj);
  setupParser(parserContext);

  try {
    parserContext.handleTokens();
  } catch (QPSSyntaxError& e) {
    return {"SyntaxError"};
  } catch (QPSSemanticError& e) {
    return {"SemanticError"};
  }

  return queryObj.evaluate();
}

void QPS::setupParser(PQLParserContext& pc) {
  unique_ptr<DeclarativeParserState> declarativeParserState =
      make_unique<DeclarativeParserState>(pc);
  pc.transitionTo(std::move(declarativeParserState));
}
