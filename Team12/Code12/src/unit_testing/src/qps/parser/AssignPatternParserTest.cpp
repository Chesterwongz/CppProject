#include <catch.hpp>
#include <memory>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/PatternClause.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"
#include "qps/query/Query.h"
#include "qps/token/PQLToken.h"

TEST_CASE("Valid Pattern a (LITERAL_REF, PARTIAL_MATCH)") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "cenX"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  parserContext.handleTokens();

  // expected query object
  Query expected(pkbReader);
  unique_ptr<Context> expectedContext = std::make_unique<Context>();
  expectedContext->addSynonym("newa", ASSIGN_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<SynonymArg> outerSynonym = std::make_unique<SynonymArg>("newa");
  unique_ptr<Ident> firstArg = std::make_unique<Ident>("cenX");
  unique_ptr<Ident> secondArg = std::make_unique<Ident>("x");
  PatternArgsStream patternArg;
  patternArg.push_back(std::move(firstArg));
  patternArg.push_back(std::move(secondArg));
  unique_ptr<PatternClause> patternClause = std::make_unique<PatternClause>(
      std::move(outerSynonym), std::move(patternArg), true);
  expected.addClause(std::move(patternClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Pattern a (LITERAL_REF, PARTIAL_EXPR_MATCH)") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "cenX"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_EXPRESSION_TOKEN, "x4 + y"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  parserContext.handleTokens();

  // expected query object
  Query expected(pkbReader);
  unique_ptr<Context> expectedContext = std::make_unique<Context>();
  expectedContext->addSynonym("newa", ASSIGN_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<SynonymArg> outerSynonym = std::make_unique<SynonymArg>("newa");
  unique_ptr<Ident> firstArg = std::make_unique<Ident>("cenX");
  unique_ptr<Ident> secondArg = std::make_unique<Ident>("x4 + y");
  PatternArgsStream patternArg;
  patternArg.push_back(std::move(firstArg));
  patternArg.push_back(std::move(secondArg));
  unique_ptr<PatternClause> patternClause = std::make_unique<PatternClause>(
      std::move(outerSynonym), std::move(patternArg), true);
  expected.addClause(std::move(patternClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Pattern a (SYNONYM, PARTIAL_MATCH)") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  parserContext.handleTokens();

  // expected query object
  Query expected(pkbReader);
  unique_ptr<Context> expectedContext = std::make_unique<Context>();
  expectedContext->addSynonym(a1, ASSIGN_ENTITY);
  expectedContext->addSynonym(var1, VARIABLE_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<SynonymArg> outerSynonym = std::make_unique<SynonymArg>(a1);
  unique_ptr<SynonymArg> firstArg = std::make_unique<SynonymArg>(var1);
  unique_ptr<Ident> secondArg = std::make_unique<Ident>("x");
  PatternArgsStream patternArg;
  patternArg.push_back(std::move(firstArg));
  patternArg.push_back(std::move(secondArg));
  unique_ptr<PatternClause> patternClause = std::make_unique<PatternClause>(
      std::move(outerSynonym), std::move(patternArg), true);
  expected.addClause(std::move(patternClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Pattern a (_, PARTIAL_MATCH)") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  parserContext.handleTokens();

  // expected query object
  Query expected(pkbReader);
  unique_ptr<Context> expectedContext = std::make_unique<Context>();
  expectedContext->addSynonym(a1, ASSIGN_ENTITY);
  expectedContext->addSynonym(var1, VARIABLE_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<SynonymArg> outerSynonym = std::make_unique<SynonymArg>(a1);
  unique_ptr<Wildcard> firstArg = std::make_unique<Wildcard>();
  unique_ptr<Ident> secondArg = std::make_unique<Ident>("x");
  PatternArgsStream patternArg;
  patternArg.push_back(std::move(firstArg));
  patternArg.push_back(std::move(secondArg));
  unique_ptr<PatternClause> patternClause = std::make_unique<PatternClause>(
      std::move(outerSynonym), std::move(patternArg), true);
  expected.addClause(std::move(patternClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Pattern a (SYNONYM, EXACT_MATCH)") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  parserContext.handleTokens();

  // expected query object
  Query expected(pkbReader);
  unique_ptr<Context> expectedContext = std::make_unique<Context>();
  expectedContext->addSynonym(a1, ASSIGN_ENTITY);
  expectedContext->addSynonym(var1, VARIABLE_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<SynonymArg> outerSynonym = std::make_unique<SynonymArg>(a1);
  unique_ptr<SynonymArg> firstArg = std::make_unique<SynonymArg>(var1);
  unique_ptr<Ident> secondArg = std::make_unique<Ident>("x");
  PatternArgsStream patternArg;
  patternArg.push_back(std::move(firstArg));
  patternArg.push_back(std::move(secondArg));
  unique_ptr<PatternClause> patternClause = std::make_unique<PatternClause>(
      std::move(outerSynonym), std::move(patternArg), false);
  expected.addClause(std::move(patternClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Invalid Pattern a (SYNONYM, LEFT_PARTIAL_MATCH)") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  REQUIRE_THROWS_WITH(parserContext.handleTokens(),
                      QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH);
}

TEST_CASE("Invalid Pattern a (LITERAL_REF, RIGHT_PARTIAL_MATCH)") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "newa"),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "cenX"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  REQUIRE_THROWS_WITH(parserContext.handleTokens(),
                      QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH);
}

TEST_CASE("Invalid Pattern a (SYNONYM, PARTIAL_MATCH) - non variable synonym") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, READ_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  REQUIRE_THROWS_MATCHES(parserContext.handleTokens(), QPSSemanticError,
                         Catch::Message(QPS_SEMANTIC_ERR_NOT_VAR_SYN));
}

TEST_CASE("Invalid Pattern a (LITERAL_REF, PARTIAL_MATCH) - integer entRef") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, READ_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "3"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  REQUIRE_THROWS_MATCHES(parserContext.handleTokens(), QPSSyntaxError,
                         Catch::Message(QPS_TOKENIZATION_ERR_IDENT));
}

TEST_CASE("Invalid Pattern a (SYNONYM, EXACT_EXPR_MATCH) - invalid expr") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_EXPRESSION_TOKEN, "+ x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  REQUIRE_THROWS_MATCHES(parserContext.handleTokens(), QPSSyntaxError,
                         Catch::Message(QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH));
}

TEST_CASE(
    "Invalid Pattern a (SYNONYM, EXACT_EXPR_MATCH) "
    "- invalid expr, unmatched brackets") {
  string a1 = "newa";
  string var1 = "var";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, a1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, var1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_EXPRESSION_TOKEN, "5 + (x + y"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
  };
  PQLTokenStream tokenStream(tokenList);

  PKBStorage storage{};
  PKBReader pkbReader(storage);
  Query query(pkbReader);
  PQLParserContext parserContext(tokenStream, query);
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  REQUIRE_THROWS_MATCHES(parserContext.handleTokens(), QPSSyntaxError,
                         Catch::Message(QPS_SYNTAX_ERR_INVALID_PATTERN_MATCH));
}
