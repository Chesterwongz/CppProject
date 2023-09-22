#include "catch.hpp"

#include <memory>
#include <vector>

#include "qps/tokenizer/PQLTokenType.h"
#include "qps/context/Context.h"
#include "qps/query/Query.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

using std::unique_ptr, std::make_unique, std::move, std::vector;

TEST_CASE("Invalid parser state - declarative") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "akfsdjfhs") };
    PQLTokenStream tokenStream = PQLTokenStream(make_unique<PQLTokenList>(tokenList));
//    Query query();
//
//    PQLParserContext parserContext(tokenStream, query);
//    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);

    REQUIRE_THROWS(QPSInvalidQueryException(QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN));
}
