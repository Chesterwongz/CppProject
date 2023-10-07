#include <catch.hpp>
#include <memory>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/PatternClause.h"
#include "qps/clause/suchThatClause/SuchThatClause.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"
#include "qps/query/Query.h"
#include "qps/token/PQLToken.h"

using std::unique_ptr, std::make_unique, std::move, std::vector;

TEST_CASE("Invalid parser state - declarative") {
  const string name = "akfsdjfhs";
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, name)};
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));

  REQUIRE_THROWS_WITH(parserContext.handleTokens(),
                      QPS_TOKENIZATION_ERR + name);
}

TEST_CASE("incomplete query - only declarative clause") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "a"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
  };
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));

  REQUIRE_THROWS_WITH(parserContext.handleTokens(),
                      QPS_TOKENIZATION_ERR_INCOMPLETE_DECLARATION);
}

TEST_CASE("invalid query - select undeclared synonym") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "a"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "a1"),
  };
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));

  REQUIRE_THROWS_WITH(parserContext.handleTokens(),
                      "Using undeclared synonym: a1");
}

/**
TEST_CASE("valid simple transitive follows") {
    vector<PQLToken> tokenList = { PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                   PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                   PQLToken(PQL_NAME_TOKEN, "a"),
                                   PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
                                   PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
                                   PQLToken(PQL_NAME_TOKEN,
FOLLOWS_ABSTRACTION), PQLToken(PQL_ASTERISKS_TOKEN, "*"),
                                   PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                   PQLToken(PQL_INTEGER_TOKEN, "5"),
                                   PQLToken(PQL_COMMA_TOKEN, ","),
                                   PQLToken(PQL_WILDCARD_TOKEN,
WILDCARD_KEYWORD), PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
    };
    PQLTokenStream tokenStream(tokenList);

    PKBStorage storage{};
    PKBReader pkbReader(storage);
    Query query(pkbReader);
    PQLParserContext parserContext(tokenStream, query);
    unique_ptr<DeclarativeParserState> declarativeParserState =
make_unique<DeclarativeParserState>(parserContext);
    parserContext.transitionTo(std::move(declarativeParserState));
    parserContext.handleTokens();

    // expected query object
    Query expected(pkbReader);
    unique_ptr<Context> expectedContext = make_unique<Context>();
    expectedContext->addSynonym("a", ASSIGN_ENTITY);
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
 **/

TEST_CASE("valid simple uses") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
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
  unique_ptr<DeclarativeParserState> declarativeParserState =
      make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  parserContext.handleTokens();

  // expected query object
  Query expected(pkbReader);
  unique_ptr<Context> expectedContext = make_unique<Context>();
  expectedContext->addSynonym("v", VARIABLE_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<Integer> firstArg = std::make_unique<Integer>("14");
  unique_ptr<SynonymArg> secondArg = std::make_unique<SynonymArg>("v");
  unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("valid such that before pattern") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, "assign"),
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
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  parserContext.handleTokens();

  // expected query object
  Query expected(pkbReader);
  unique_ptr<Context> expectedContext = make_unique<Context>();
  expectedContext->addSynonym("a", "assign");
  expected.addContext(std::move(expectedContext));
  unique_ptr<SynonymArg> firstSuchThatArg = std::make_unique<SynonymArg>("a");
  unique_ptr<Ident> secondSuchThatArg = std::make_unique<Ident>("x");
  unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstSuchThatArg), std::move(secondSuchThatArg));
  expected.addClause(std::move(suchThatClause));

  unique_ptr<SynonymArg> outerSynonym = std::make_unique<SynonymArg>("a");
  unique_ptr<Ident> firstPatternArg = std::make_unique<Ident>("x");
  unique_ptr<Wildcard> secondPatternArg = std::make_unique<Wildcard>();
  vector<unique_ptr<AbstractArgument>> patternArg;
  patternArg.push_back(std::move(firstPatternArg));
  patternArg.push_back(std::move(secondPatternArg));
  unique_ptr<PatternClause> patternClause = make_unique<PatternClause>(
      std::move(outerSynonym), std::move(patternArg), false);
  expected.addClause(std::move(patternClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("invalid query - Uses clause only has 1 argument") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
                                PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_WILDCARD_TOKEN, "_"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  REQUIRE_THROWS_WITH(parserContext.handleTokens(),
                      QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT);
}

TEST_CASE("invalid query - Pattern clause only has 1 argument") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
                                PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_WILDCARD_TOKEN, "_"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  REQUIRE_THROWS_WITH(parserContext.handleTokens(),
                      QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH);
}

TEST_CASE("valid pattern before such that") {
  vector<PQLToken> tokenList = {PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_SEMICOLON_TOKEN, ";"),
                                PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_WILDCARD_TOKEN, "_"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
                                PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
                                PQLToken(PQL_NAME_TOKEN, USES_ABSTRACTION),
                                PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
                                PQLToken(PQL_NAME_TOKEN, "a"),
                                PQLToken(PQL_COMMA_TOKEN, ","),
                                PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
                                PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  parserContext.handleTokens();

  // expected query object
  Query expected(pkbReader);

  unique_ptr<SynonymArg> outerSynonym = std::make_unique<SynonymArg>("a");
  unique_ptr<Ident> firstPatternArg = std::make_unique<Ident>("x");
  unique_ptr<Wildcard> secondPatternArg = std::make_unique<Wildcard>();
  PatternArgsStream patternArg;
  patternArg.push_back(std::move(firstPatternArg));
  patternArg.push_back(std::move(secondPatternArg));
  unique_ptr<PatternClause> patternClause = make_unique<PatternClause>(
      std::move(outerSynonym), std::move(patternArg), false);
  expected.addClause(std::move(patternClause));

  unique_ptr<Context> expectedContext = make_unique<Context>();
  expectedContext->addSynonym("a", "assign");
  expected.addContext(std::move(expectedContext));
  unique_ptr<SynonymArg> firstSuchThatArg = std::make_unique<SynonymArg>("a");
  unique_ptr<Ident> secondSuchThatArg = std::make_unique<Ident>("x");
  unique_ptr<SuchThatClause> suchThatClause = make_unique<SuchThatClause>(
      USES_ENUM, std::move(firstSuchThatArg), std::move(secondSuchThatArg));
  expected.addClause(std::move(suchThatClause));

  bool res = query == expected;
  REQUIRE(res);
}
