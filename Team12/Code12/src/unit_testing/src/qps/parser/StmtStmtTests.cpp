// TEMP_CATCH_INCLUDE
#include <memory>
#include <vector>

#include "pkb/facade/PKBReader.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/suchThatClause/SuchThatClause.h"
#include "qps/parser/PQLParserContext.h"
#include "qps/parser/declarativeParserState/DeclarativeParserState.h"
#include "qps/query/Query.h"
#include "qps/token/PQLToken.h"

TEST_CASE("Valid Follows(SYNONYM, SYNONYM)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
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
  expectedContext->addSynonym(d1, STMT_ENTITY);
  expectedContext->addSynonym(d2, ASSIGN_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<SynonymArg> firstArg = std::make_unique<SynonymArg>(d1);
  unique_ptr<SynonymArg> secondArg = std::make_unique<SynonymArg>(d2);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Follows(SYNONYM, _)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_COMMA_TOKEN, ","),
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
  expectedContext->addSynonym(d1, STMT_ENTITY);
  expectedContext->addSynonym(d2, ASSIGN_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<SynonymArg> firstArg = std::make_unique<SynonymArg>(d1);
  unique_ptr<Wildcard> secondArg = std::make_unique<Wildcard>();
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Follows(SYNONYM, INTEGER)") {
  string d1 = "hello";
  string d2 = "assign";
  string int1 = "5";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_INTEGER_TOKEN, int1),
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
  expectedContext->addSynonym(d1, STMT_ENTITY);
  expectedContext->addSynonym(d2, ASSIGN_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<SynonymArg> firstArg = std::make_unique<SynonymArg>(d1);
  unique_ptr<Integer> secondArg = std::make_unique<Integer>(int1);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Follows(_, SYNONYM)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
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
  expectedContext->addSynonym(d1, STMT_ENTITY);
  expectedContext->addSynonym(d2, ASSIGN_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<Wildcard> firstArg = std::make_unique<Wildcard>();
  unique_ptr<SynonymArg> secondArg = std::make_unique<SynonymArg>(d2);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Follows(_, _)") {
  string d1 = "hello";
  string d2 = "assign";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
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
  expectedContext->addSynonym(d1, STMT_ENTITY);
  expectedContext->addSynonym(d2, ASSIGN_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<Wildcard> firstArg = std::make_unique<Wildcard>();
  unique_ptr<Wildcard> secondArg = std::make_unique<Wildcard>();
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Follows(_, INTEGER)") {
  string d1 = "hello";
  string d2 = "assign";
  string int1 = "8";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_INTEGER_TOKEN, int1),
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
  expectedContext->addSynonym(d1, STMT_ENTITY);
  expectedContext->addSynonym(d2, ASSIGN_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<Wildcard> firstArg = std::make_unique<Wildcard>();
  unique_ptr<Integer> secondArg = std::make_unique<Integer>(int1);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Follows(INTEGER, SYNONYM)") {
  string d1 = "hello";
  string d2 = "assign";
  string int1 = "4";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_INTEGER_TOKEN, int1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
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
  expectedContext->addSynonym(d1, STMT_ENTITY);
  expectedContext->addSynonym(d2, ASSIGN_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<Integer> firstArg = std::make_unique<Integer>(int1);
  unique_ptr<SynonymArg> secondArg = std::make_unique<SynonymArg>(d2);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Follows(INTEGER, _)") {
  string d1 = "hello";
  string d2 = "assign";
  string int1 = "4";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_INTEGER_TOKEN, int1),
      PQLToken(PQL_COMMA_TOKEN, ","),
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
  expectedContext->addSynonym(d1, STMT_ENTITY);
  expectedContext->addSynonym(d2, ASSIGN_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<Integer> firstArg = std::make_unique<Integer>(int1);
  unique_ptr<Wildcard> secondArg = std::make_unique<Wildcard>();
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Follows(INTEGER, INTEGER)") {
  string d1 = "hello";
  string d2 = "assign";
  string int1 = "4";
  string int2 = "6";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_INTEGER_TOKEN, int1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_INTEGER_TOKEN, int2),
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
  expectedContext->addSynonym(d1, STMT_ENTITY);
  expectedContext->addSynonym(d2, ASSIGN_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<Integer> firstArg = std::make_unique<Integer>(int1);
  unique_ptr<Integer> secondArg = std::make_unique<Integer>(int2);
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Follows(SYNONYM, _) - keyword as synonym") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_COMMA_TOKEN, ","),
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
  expectedContext->addSynonym("Follows", STMT_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<SynonymArg> firstArg =
      std::make_unique<SynonymArg>(FOLLOWS_ABSTRACTION);
  unique_ptr<Wildcard> secondArg = std::make_unique<Wildcard>();
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid Parents(SYNONYM, SYNONYM)") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "a"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, STMT_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "w"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "a"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, PARENTS_ABSTRACTION),
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
  unique_ptr<DeclarativeParserState> declarativeParserState =
      std::make_unique<DeclarativeParserState>(parserContext);
  parserContext.transitionTo(std::move(declarativeParserState));
  parserContext.handleTokens();

  // expected query object
  Query expected(pkbReader);
  unique_ptr<Context> expectedContext = std::make_unique<Context>();
  expectedContext->addSynonym("a", ASSIGN_ENTITY);
  expectedContext->addSynonym("w", STMT_ENTITY);
  expected.addContext(std::move(expectedContext));
  unique_ptr<SynonymArg> firstArg = std::make_unique<SynonymArg>("w");
  unique_ptr<SynonymArg> secondArg = std::make_unique<SynonymArg>("a");
  unique_ptr<SuchThatClause> suchThatClause = std::make_unique<SuchThatClause>(
      PARENTS_ENUM, std::move(firstArg), std::move(secondArg));
  expected.addClause(std::move(suchThatClause));

  bool res = query == expected;
  REQUIRE(res);
}

TEST_CASE("Invalid Parents(SYNONYM, SYNONYM) - both are not stmt synonyms") {
  string d1 = "hello";
  string d2 = "assign";
  string int1 = "4";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, WHILE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, PROCEDURE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, d2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, d1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, d2),
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
                         Catch::Message(QPS_SEMANTIC_ERR_NOT_STMT_SYN));
}

TEST_CASE("Invalid Parent clause - undeclared synonym") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, PARENTS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, "a"),
      PQLToken(PQL_COMMA_TOKEN, ","),
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
                      "Using undeclared synonym: a");
}

TEST_CASE("Invalid Parent clause - invalid LITERAL_REF_TOKEN") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, PARENTS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "a"),
      PQLToken(PQL_COMMA_TOKEN, ","),
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
  REQUIRE_THROWS_MATCHES(
      parserContext.handleTokens(), QPSSyntaxError,
      Catch::Message("Error occurred during tokenization, invalid token: a"));
}

TEST_CASE("Invalid Parent clause - only 1 argument") {
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, VARIABLE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_SELECT_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, "v"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, PARENTS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
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

  REQUIRE_THROWS_MATCHES(
      parserContext.handleTokens(), QPSSyntaxError,
      Catch::Message(QPS_TOKENIZATION_ERR_INCORRECT_ARGUMENT));
}
