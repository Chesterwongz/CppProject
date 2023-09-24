#include "catch.hpp"

#include <memory>
#include <vector>

#include "qps/query/Query.h"
#include "qps/token/PQLToken.h"
#include "qps/parser/PQLParserContext.h"
#include "pkb/facade/PKBReader.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"
#include "qps/exceptions/QPSInvalidQueryException.h"
#include "qps/clause/suchThatClause/SuchThatClause.h"
#include "qps/clause/patternClause/PatternClause.h"
#include "qps/argument/argumentFactory/ArgumentFactory.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/wildcard/Wildcard.h"

using std::unique_ptr, std::make_unique, std::move, std::vector;

TEST_CASE("Invalid parser state - declarative") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "akfsdjfhs") };
    PQLTokenStream tokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(std::move(declarativeParserState));

    REQUIRE_THROWS_WITH(parserContext.handleTokens(), QPS_INVALID_QUERY_ERR_UNEXPECTED_TOKEN);
}

TEST_CASE("incomplete query - only declarative clause") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "assign"),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   };
    PQLTokenStream tokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(std::move(declarativeParserState));

    REQUIRE_THROWS_WITH(parserContext.handleTokens(), QPS_INVALID_QUERY_INCOMPLETE_QUERY);
}

TEST_CASE("invalid query - select invalid synonym") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "assign"),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_SELECT_TOKEN, "Select"),
                                   PQLToken(PQL_NAME_TOKEN, "a1"),
    };
    PQLTokenStream tokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(std::move(declarativeParserState));
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
    PQLTokenStream tokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(std::move(declarativeParserState));
    parserContext.handleTokens();

    // expected query object
    Query expected(pkbReader);
    unique_ptr<Context> expectedContext = make_unique<Context>();
    expectedContext->addSynonym("a", "assign");
    expected.addContext(std::move(expectedContext));
    unique_ptr<Integer> firstArg = ArgumentFactory::createIntegerArgument("5");
    unique_ptr<Wildcard> secondArg = ArgumentFactory::createWildcardArgument();
    unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
            FOLLOWS_ENUM,
            std::move(firstArg),
            std::move(secondArg),
            true);
    expected.addClause(std::move(suchThatClause));

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
    PQLTokenStream tokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(std::move(declarativeParserState));
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
    PQLTokenStream tokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(std::move(declarativeParserState));
    parserContext.handleTokens();

    // expected query object
    Query expected(pkbReader);
    unique_ptr<Context> expectedContext = make_unique<Context>();
    expectedContext->addSynonym("a", "assign");
    expectedContext->addSynonym("w", "while");
    expected.addContext(std::move(expectedContext));
    unique_ptr<SynonymArg> firstArg = ArgumentFactory::createSynonymArgument("w");
    unique_ptr<SynonymArg> secondArg = ArgumentFactory::createSynonymArgument("a");
    unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
            PARENTS_ENUM,
            std::move(firstArg),
            std::move(secondArg),
            false);
    expected.addClause(std::move(suchThatClause));

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
    PQLTokenStream tokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(std::move(declarativeParserState));
    parserContext.handleTokens();

    // expected query object
    Query expected(pkbReader);
    unique_ptr<Context> expectedContext = make_unique<Context>();
    expectedContext->addSynonym("v", "variable");
    expected.addContext(std::move(expectedContext));
    unique_ptr<Integer> firstArg = ArgumentFactory::createIntegerArgument("6");
    unique_ptr<SynonymArg> secondArg = ArgumentFactory::createSynonymArgument("v");
    unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
            MODIFIES_ENUM,
            std::move(firstArg),
            std::move(secondArg),
            false);
    expected.addClause(std::move(suchThatClause));

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
    PQLTokenStream tokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(std::move(declarativeParserState));
    parserContext.handleTokens();

    // expected query object
    Query expected(pkbReader);
    unique_ptr<Context> expectedContext = make_unique<Context>();
    expectedContext->addSynonym("v", "variable");
    expected.addContext(std::move(expectedContext));
    unique_ptr<Integer> firstArg = ArgumentFactory::createIntegerArgument("14");
    unique_ptr<SynonymArg> secondArg = ArgumentFactory::createSynonymArgument("v");
    unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
            USES_ENUM,
            std::move(firstArg),
            std::move(secondArg),
            false);
    expected.addClause(std::move(suchThatClause));

    bool res = query == expected;
    REQUIRE(res);
}

TEST_CASE("valid pattern partial match") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "assign"),
                                   PQLToken(PQL_NAME_TOKEN, "newa"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_SELECT_TOKEN, "Select"),
                                   PQLToken(PQL_NAME_TOKEN, "newa"),
                                   PQLToken(PQL_NAME_TOKEN, "pattern"),
                                   PQLToken(PQL_NAME_TOKEN, "newa"),
                                   PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                   PQLToken(PQL_LITERAL_REF_TOKEN, "cenX"),
                                   PQLToken(PQL_COMMA_TOKEN, ","),
                                   PQLToken(PQL_WILDCARD_TOKEN, "_"),
                                   PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                   PQLToken(PQL_WILDCARD_TOKEN, "_"),
                                   PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
    };
    PQLTokenStream tokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(std::move(declarativeParserState));
    parserContext.handleTokens();

    // expected query object
    Query expected(pkbReader);
    unique_ptr<Context> expectedContext = make_unique<Context>();
    expectedContext->addSynonym("newa", "assign");
    expected.addContext(std::move(expectedContext));
    unique_ptr<SynonymArg> outerSynonym = ArgumentFactory::createSynonymArgument("newa");
    unique_ptr<Ident> firstArg = ArgumentFactory::createIdentArgument("cenX");
    unique_ptr<Ident> secondArg = ArgumentFactory::createIdentArgument("x");
    vector<unique_ptr<IArgument>> patternArg;
    patternArg.push_back(std::move(firstArg));
    patternArg.push_back(std::move(secondArg));
    unique_ptr<PatternClause> patternClause = make_unique<PatternClause>(
            std::move(outerSynonym),
            make_unique<vector<unique_ptr<IArgument>>>(std::move(patternArg)),
            true
            );
    expected.addClause(std::move(patternClause));

    bool res = query == expected;
    REQUIRE(res);
}


TEST_CASE("invalid pattern partial match - front only") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "assign"),
                                   PQLToken(PQL_NAME_TOKEN, "newa"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_SELECT_TOKEN, "Select"),
                                   PQLToken(PQL_NAME_TOKEN, "newa"),
                                   PQLToken(PQL_NAME_TOKEN, "pattern"),
                                   PQLToken(PQL_NAME_TOKEN, "newa"),
                                   PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                   PQLToken(PQL_LITERAL_REF_TOKEN, "cenX"),
                                   PQLToken(PQL_COMMA_TOKEN, ","),
                                   PQLToken(PQL_WILDCARD_TOKEN, "_"),
                                   PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                   PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
    };
    PQLTokenStream tokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(std::move(declarativeParserState));
    REQUIRE_THROWS_WITH(parserContext.handleTokens(), QPS_INVALID_QUERY_INCOMPLETE_PARTIAL_MATCH_PATTERN);
}

TEST_CASE("invalid pattern partial match - back only") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "assign"),
                                   PQLToken(PQL_NAME_TOKEN, "newa"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_SELECT_TOKEN, "Select"),
                                   PQLToken(PQL_NAME_TOKEN, "newa"),
                                   PQLToken(PQL_NAME_TOKEN, "pattern"),
                                   PQLToken(PQL_NAME_TOKEN, "newa"),
                                   PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                   PQLToken(PQL_LITERAL_REF_TOKEN, "cenX"),
                                   PQLToken(PQL_COMMA_TOKEN, ","),
                                   PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                   PQLToken(PQL_WILDCARD_TOKEN, "_"),
                                   PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
    };
    PQLTokenStream tokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(std::move(declarativeParserState));
    REQUIRE_THROWS_WITH(parserContext.handleTokens(), QPS_INVALID_QUERY_INCOMPLETE_PARTIAL_MATCH_PATTERN);
}


// this test will fail
// TODO: debug pattern parser state
TEST_CASE("valid such that before pattern") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, "assign"),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_SELECT_TOKEN, "Select"),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_NAME_TOKEN, "such"),
                                   PQLToken(PQL_NAME_TOKEN, "that"),
                                   PQLToken(PQL_NAME_TOKEN, "Uses"),
                                   PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_COMMA_TOKEN, ","),
                                   PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                   PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
                                   PQLToken(PQL_NAME_TOKEN, "pattern"),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                   PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                   PQLToken(PQL_COMMA_TOKEN, ","),
                                   PQLToken(PQL_WILDCARD_TOKEN, "_"),
                                   PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")
    };
    PQLTokenStream tokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState = make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(std::move(declarativeParserState));
    parserContext.handleTokens();

    // expected query object
    Query expected(pkbReader);
    unique_ptr<Context> expectedContext = make_unique<Context>();
    expectedContext->addSynonym("a", "assign");
    expected.addContext(std::move(expectedContext));
    unique_ptr<SynonymArg> firstSuchThatArg = ArgumentFactory::createSynonymArgument("a");
    unique_ptr<Ident> secondSuchThatArg = ArgumentFactory::createIdentArgument("x");
    unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
            USES_ENUM,
            std::move(firstSuchThatArg),
            std::move(secondSuchThatArg),
            false);
    expected.addClause(std::move(suchThatClause));

    unique_ptr<SynonymArg> outerSynonym = ArgumentFactory::createSynonymArgument("a");
    unique_ptr<Ident> firstPatternArg = ArgumentFactory::createIdentArgument("x");
    unique_ptr<Wildcard> secondPatternArg = ArgumentFactory::createWildcardArgument();
    vector<unique_ptr<IArgument>> patternArg;
    patternArg.push_back(std::move(firstPatternArg));
    patternArg.push_back(std::move(secondPatternArg));
    unique_ptr<PatternClause> patternClause = make_unique<PatternClause>(
            std::move(outerSynonym),
            make_unique<vector<unique_ptr<IArgument>>>(std::move(patternArg)),
            true
    );
    expected.addClause(std::move(patternClause));

    bool res = query == expected;
    REQUIRE(res);
}
