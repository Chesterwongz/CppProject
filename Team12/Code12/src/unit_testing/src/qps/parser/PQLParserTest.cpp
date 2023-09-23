#include "catch.hpp"

#include <memory>
#include <vector>

#include "qps/tokenizer/PQLTokenType.h"
#include "qps/query/Query.h"
#include "qps/parser/PQLParserContext.h"
#include "pkb/facade/PKBReader.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"
#include "qps/exceptions/QPSInvalidQueryException.h"

using std::unique_ptr, std::make_unique, std::move, std::vector;

TEST_CASE("Invalid parser state - declarative") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "akfsdjfhs") };
    PQLTokenStream tokenStream = PQLTokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(move(declarativeParserState));

    REQUIRE_THROWS_WITH(parserContext.handleTokens(), QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
}

TEST_CASE("incomplete query - only declarative clause") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "assign"),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   };
    PQLTokenStream tokenStream = PQLTokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(move(declarativeParserState));

    REQUIRE_THROWS_WITH(parserContext.handleTokens(), QPS_INVALID_QUERY_INCOMPLETE_QUERY);
}

TEST_CASE("invalid query - select invalid synonym") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "assign"),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_SELECT_TOKEN, "Select"),
                                   PQLToken(PQL_NAME_TOKEN, "a1"),
    };
    PQLTokenStream tokenStream = PQLTokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(move(declarativeParserState));
    parserContext.handleTokens();
    // TODO: throw when Select Clause is added
}

TEST_CASE("valid simple transitive follows") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "assign"),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_SELECT_TOKEN, "Select"),
                                   PQLToken(PQL_NAME_TOKEN, "a1"),
                                   PQLToken(PQL_NAME_TOKEN, "such"),
                                   PQLToken(PQL_NAME_TOKEN, "that"),
                                   PQLToken(PQL_NAME_TOKEN, "Follows"),
                                   PQLToken(PQL_ASTERISKS_TOKEN, "*"),
                                   PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                   PQLToken(PQL_INTEGER_TOKEN, "5"),
                                   PQLToken(PQL_COMMA_TOKEN, ","),
                                   PQLToken(PQL_WILDCARD_TOKEN, "_"),
                                   PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
    };
    PQLTokenStream tokenStream = PQLTokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(move(declarativeParserState));
    parserContext.handleTokens();
    // TODO: check if query equals
}
