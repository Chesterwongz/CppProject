#include <utility>
#include <vector>
#include <memory>

#include "QPS.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"

using std::string, std::vector, std::unique_ptr;

// TODO: test
QPS::QPS(PKBReader &pkb, const string& query) :
    pkb(pkb),
    tokenizer(PQLTokenizer(query)) {}

std::set<string> QPS::processQueryString() {
    unique_ptr<PQLTokenList> tokenList = tokenizer.tokenize();
    PQLTokenStream tokenStream = PQLTokenStream(*tokenList);

    Query query(pkb);

    PQLParserContext parserContext(tokenStream, query);
    setupParser(parserContext);

    parserContext.handleTokens();

    return query.evaluate();
}

void QPS::setupParser(PQLParserContext& pc) {
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(pc);
    pc.transitionTo(move(declarativeParserState));

}
