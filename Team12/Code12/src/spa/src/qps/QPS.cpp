#include "QPS.h"

QPS::QPS(PKBReader& pkb) : pkb(pkb) {}

unordered_set<string> QPS::processQueryString(const string& query) {
  unique_ptr<Query> queryObj = std::make_unique<Query>(pkb);
  try {
    unique_ptr<PQLTokenStream> tokenStream = PQLTokenizer::tokenize(query);

    PQLParserContext parserContext(std::move(tokenStream), queryObj);
    setupParser(parserContext);
    parserContext.handleTokens();

    return queryObj->evaluate();
  } catch (CommonSyntaxError& e) {
    return {"SyntaxError"};
  } catch (QPSSyntaxError& e) {
    return {"SyntaxError"};
  } catch (QPSSemanticError& e) {
    return {"SemanticError"};
  }
}

void QPS::setupParser(PQLParserContext& pc) {
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(pc);
  pc.transitionTo(std::move(declarativeParserState));
}
