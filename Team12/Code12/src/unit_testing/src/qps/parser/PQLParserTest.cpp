#include "catch.hpp"

#include <memory>
#include <vector>

#include "qps/tokenizer/PQLTokenType.h"
#include "qps/query/Query.h"
#include "qps/token/PQLToken.h"
#include "qps/parser/PQLParserContext.h"
#include "pkb/facade/PKBReader.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"
#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/clause/suchThatClause/SuchThatClause.h"
#include "qps/argument/argumentFactory/ArgumentFactory.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/wildcard/Wildcard.h"

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
    REQUIRE_THROWS_WITH(parserContext.handleTokens(), QPS_INVALID_QUERY_ERR_INVALID_SYNONYM);
}

TEST_CASE("valid simple transitive follows") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "assign"),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_SELECT_TOKEN, "Select"),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
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

    // expected query object
    Query expected(pkbReader);
    unique_ptr<Context> expectedContext = make_unique<Context>();
    expectedContext->addSynonym("a", "assign");
    expected.addContext(move(expectedContext));
    unique_ptr<Integer> firstArg = ArgumentFactory::createIntegerArgument("5");
    unique_ptr<Wildcard> secondArg = ArgumentFactory::createWildcardArgument();
    unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
            FOLLOWS_ENUM,
            move(firstArg),
            move(secondArg),
            true);
    expected.addClause(move(suchThatClause));

    bool res = query == expected;
    REQUIRE(res);
}

TEST_CASE("invalid simple parent - invalid synonym") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "variable"),
                                   PQLToken(PQL_NAME_TOKEN, "v"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_SELECT_TOKEN, "Select"),
                                   PQLToken(PQL_NAME_TOKEN, "v"),
                                   PQLToken(PQL_NAME_TOKEN, "such"),
                                   PQLToken(PQL_NAME_TOKEN, "that"),
                                   PQLToken(PQL_NAME_TOKEN, "Parent"),
                                   PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
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
    REQUIRE_THROWS_WITH(parserContext.handleTokens(), QPS_INVALID_QUERY_ERR_INVALID_SYNONYM);
}

TEST_CASE("valid simple parent") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "assign"),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_NAME_TOKEN, "while"),
                                   PQLToken(PQL_NAME_TOKEN, "w"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_SELECT_TOKEN, "Select"),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_NAME_TOKEN, "such"),
                                   PQLToken(PQL_NAME_TOKEN, "that"),
                                   PQLToken(PQL_NAME_TOKEN, "Parent"),
                                   PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                   PQLToken(PQL_NAME_TOKEN, "w"),
                                   PQLToken(PQL_COMMA_TOKEN, ","),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
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

    // expected query object
    Query expected(pkbReader);
    unique_ptr<Context> expectedContext = make_unique<Context>();
    expectedContext->addSynonym("a", "assign");
    expectedContext->addSynonym("w", "while");
    expected.addContext(move(expectedContext));
    unique_ptr<SynonymArg> firstArg = ArgumentFactory::createSynonymArgument("w");
    unique_ptr<SynonymArg> secondArg = ArgumentFactory::createSynonymArgument("a");
    unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
            PARENTS_ENUM,
            move(firstArg),
            move(secondArg),
            false);
    expected.addClause(move(suchThatClause));

    bool res = query == expected;
    REQUIRE(res);
}



TEST_CASE("valid simple modifies") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "variable"),
                                   PQLToken(PQL_NAME_TOKEN, "v"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_SELECT_TOKEN, "Select"),
                                   PQLToken(PQL_NAME_TOKEN, "v"),
                                   PQLToken(PQL_NAME_TOKEN, "such"),
                                   PQLToken(PQL_NAME_TOKEN, "that"),
                                   PQLToken(PQL_NAME_TOKEN, "Modifies"),
                                   PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                   PQLToken(PQL_INTEGER_TOKEN, "6"),
                                   PQLToken(PQL_COMMA_TOKEN, ","),
                                   PQLToken(PQL_NAME_TOKEN, "v"),
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

    // expected query object
    Query expected(pkbReader);
    unique_ptr<Context> expectedContext = make_unique<Context>();
    expectedContext->addSynonym("v", "variable");
    expected.addContext(move(expectedContext));
    unique_ptr<Integer> firstArg = ArgumentFactory::createIntegerArgument("6");
    unique_ptr<SynonymArg> secondArg = ArgumentFactory::createSynonymArgument("v");
    unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
            MODIFIES_ENUM,
            move(firstArg),
            move(secondArg),
            false);
    expected.addClause(move(suchThatClause));

    bool res = query == expected;
    REQUIRE(res);
}

TEST_CASE("valid simple uses") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "variable"),
                                   PQLToken(PQL_NAME_TOKEN, "v"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_SELECT_TOKEN, "Select"),
                                   PQLToken(PQL_NAME_TOKEN, "v"),
                                   PQLToken(PQL_NAME_TOKEN, "such"),
                                   PQLToken(PQL_NAME_TOKEN, "that"),
                                   PQLToken(PQL_NAME_TOKEN, "Uses"),
                                   PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                   PQLToken(PQL_INTEGER_TOKEN, "14"),
                                   PQLToken(PQL_COMMA_TOKEN, ","),
                                   PQLToken(PQL_NAME_TOKEN, "v"),
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

    // expected query object
    Query expected(pkbReader);
    unique_ptr<Context> expectedContext = make_unique<Context>();
    expectedContext->addSynonym("v", "variable");
    expected.addContext(move(expectedContext));
    unique_ptr<Integer> firstArg = ArgumentFactory::createIntegerArgument("14");
    unique_ptr<SynonymArg> secondArg = ArgumentFactory::createSynonymArgument("v");
    unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
            USES_ENUM,
            move(firstArg),
            move(secondArg),
            false);
    expected.addClause(move(suchThatClause));

    bool res = query == expected;
    REQUIRE(res);
}
