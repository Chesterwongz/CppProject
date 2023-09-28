#include <utility>
#include <vector>
#include <memory>

#include "QPS.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"
#include "qps/tokenizer/TokenizerFactory.h"

using std::string, std::vector, std::unique_ptr;

// TODO: test
QPS::QPS(PKBReader &pkb) :
    pkb(pkb),
    tokenizerFactory() {}

std::set<string> QPS::processQueryString(const string& query) {
    unique_ptr<PQLTokenizer> tokenizer = tokenizerFactory.makeTokenizer(query);
    std::cout << "0" << std::endl;
    unique_ptr<PQLTokenList> tokenList = tokenizer->tokenize();
    std::cout << "1" << std::endl;
    PQLTokenStream tokenStream(*tokenList);
    std::cout << "2" << std::endl;
    Query queryObj(pkb);
    std::cout << "3" << std::endl;
    PQLParserContext parserContext(tokenStream, queryObj);
    std::cout << "4" << std::endl;
    setupParser(parserContext);
    std::cout << "5" << std::endl;
    parserContext.handleTokens();

    return queryObj.evaluate();
}

void QPS::setupParser(PQLParserContext& pc) {
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(pc);
    pc.transitionTo(move(declarativeParserState));

}
