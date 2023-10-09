#include "QPS.h"

QPS::QPS(PKBReader& pkb) : pkb(pkb) {}

std::set<string> QPS::processQueryString(const string& query) {
  Query queryObj(pkb);
  try {
    unique_ptr<PQLTokenStream> tokenStream = PQLTokenizer::tokenize(query);

    PQLParserContext parserContext(std::move(tokenStream), queryObj);
    setupParser(parserContext);
    parserContext.handleTokens();

    return queryObj.evaluate();

  } catch (CommonSyntaxError& e) {
    std::cout << e.what() << std::endl;
    return {"SyntaxError"};
  } catch (QPSSyntaxError& e) {
    std::cout << e.what() << std::endl;
    return {"SyntaxError"};
  } catch (QPSSemanticError& e) {
    std::cout << e.what() << std::endl;
    return {"SemanticError"};
  }
}

void QPS::setupParser(PQLParserContext& pc) {
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(pc);
  pc.transitionTo(std::move(declarativeParserState));
}
