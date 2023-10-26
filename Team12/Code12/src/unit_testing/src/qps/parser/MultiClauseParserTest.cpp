#include <memory>
#include <vector>
#include <catch.hpp>

#include "PQLParserTestUtils.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/patternExp/PatternExp.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/patternClause/AssignPatternClause.h"
#include "qps/clause/suchThatClause/SuchThatClause.h"
#include "qps/parser/tokenizer/token/PQLToken.h"
#include "qps/query/Query.h"

TEST_CASE("Wiki Example - only such that clauses") {
  string syn1 = "a";
  string syn2 = "w";
  vector<PQLToken> tokenList1 = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, syn1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, WHILE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, syn2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, syn1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, MODIFIES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, syn1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
      PQLToken(PQL_NAME_TOKEN, AND_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, PARENTS_STAR_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, syn2),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, syn1),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
      PQLToken(PQL_NAME_TOKEN, AND_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, NEXT_STAR_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_INTEGER_TOKEN, "1"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, syn1),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};

  vector<PQLToken> tokenList2 = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, syn1),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, WHILE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, syn2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, syn1),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, MODIFIES_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, syn1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
      PQLToken(PQL_NAME_TOKEN, AND_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, PARENTS_STAR_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, syn2),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, syn1),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, NEXT_STAR_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_INTEGER_TOKEN, "1"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, syn1),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};

  std::unique_ptr<Query> query1 =
      parseToQuery(tokenList1);

  std::unique_ptr<Query> query2 =
      parseToQuery(tokenList2);

  bool res = *query1 == *query2;
  REQUIRE(res);
}

TEST_CASE("Valid pattern a and if") {
  /**
   * assign a1, a2; while w1, w2;
   * Select a2 pattern a1 ("x", _) and a2 ("x", _"x"_)
   * such that Follows (a1, a2) and Parent* (w2, a2) and Parent* (w1, w2)
   */

  string ass1 = "a1";
  string ass2 = "a2";
  string while1 = "w1";
  string while2 = "w2";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, ass1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, ass2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, WHILE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, while1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, while2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ass2),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ass1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
      PQLToken(PQL_NAME_TOKEN, AND_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ass2),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, ass1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, ass2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
      PQLToken(PQL_NAME_TOKEN, AND_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, PARENTS_STAR_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, while2),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, ass2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
      PQLToken(PQL_NAME_TOKEN, AND_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, PARENTS_STAR_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, while1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, while2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};

  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  vector<unique_ptr<SynonymArg>> synonymsToSelect = {};
  synonymsToSelect.push_back(std::make_unique<SynonymArg>(ass2, ASSIGN_ENTITY));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  // pattern a1 ("x", _)
  unique_ptr<SynonymArg> outerSyn1 =
      std::make_unique<SynonymArg>(ass1, ASSIGN_ENTITY);
  unique_ptr<Ident> firstArg1 = std::make_unique<Ident>("x");
  unique_ptr<Wildcard> secondArg1 = std::make_unique<Wildcard>();
  unique_ptr<AssignPatternClause> patternClause1 =
      std::make_unique<AssignPatternClause>(std::move(outerSyn1),
                                            std::move(firstArg1),
                                            std::move(secondArg1), false);
  expected.addClause(std::move(patternClause1));

  // pattern a2 ("x", _"x"_)
  unique_ptr<SynonymArg> outerSyn2 =
      std::make_unique<SynonymArg>(ass2, ASSIGN_ENTITY);
  unique_ptr<Ident> firstArg2 = std::make_unique<Ident>("x");
  unique_ptr<PatternExp> secondArg2 = std::make_unique<PatternExp>("x");
  unique_ptr<AssignPatternClause> patternClause2 =
      std::make_unique<AssignPatternClause>(std::move(outerSyn2),
                                            std::move(firstArg2),
                                            std::move(secondArg2), true);
  expected.addClause(std::move(patternClause2));

  // Follows (a1, a2)
  unique_ptr<SynonymArg> firstArg3 =
      std::make_unique<SynonymArg>(ass1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> secondArg3 =
      std::make_unique<SynonymArg>(ass2, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause1 = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(firstArg3), std::move(secondArg3));
  expected.addClause(std::move(suchThatClause1));

  // Parent* (w1, a2)
  unique_ptr<SynonymArg> firstArg4 =
      std::make_unique<SynonymArg>(while2, WHILE_ENTITY);
  unique_ptr<SynonymArg> secondArg4 =
      std::make_unique<SynonymArg>(ass2, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause4 = std::make_unique<SuchThatClause>(
      PARENTS_STAR_ENUM, std::move(firstArg4), std::move(secondArg4));
  expected.addClause(std::move(suchThatClause4));

  // Parent* (w1, w2)
  unique_ptr<SynonymArg> firstArg5 =
      std::make_unique<SynonymArg>(while1, WHILE_ENTITY);
  unique_ptr<SynonymArg> secondArg5 =
      std::make_unique<SynonymArg>(while2, WHILE_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause5 = std::make_unique<SuchThatClause>(
      PARENTS_STAR_ENUM, std::move(firstArg5), std::move(secondArg5));
  expected.addClause(std::move(suchThatClause5));

  bool res = *query == expected;
  REQUIRE(res);
}

TEST_CASE("Valid pattern not a and not if") {
  /**
   * assign a1, a2; while w1, w2;
   * Select a2 pattern not a1 ("x", _) and not a2 ("x", _"x"_)
   * such that not Follows (a1, a2) and not Parent* (w2, a2) and not Parent*
   * (w1, w2)
   */

  string ass1 = "a1";
  string ass2 = "a2";
  string while1 = "w1";
  string while2 = "w2";
  vector<PQLToken> tokenList = {
      PQLToken(PQL_NAME_TOKEN, ASSIGN_ENTITY),
      PQLToken(PQL_NAME_TOKEN, ass1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, ass2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, WHILE_ENTITY),
      PQLToken(PQL_NAME_TOKEN, while1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, while2),
      PQLToken(PQL_SEMICOLON_TOKEN, ";"),
      PQLToken(PQL_NAME_TOKEN, SELECT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ass2),
      PQLToken(PQL_NAME_TOKEN, PATTERN_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, NOT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ass1),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
      PQLToken(PQL_NAME_TOKEN, AND_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, NOT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, ass2),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_LITERAL_REF_TOKEN, "x"),
      PQLToken(PQL_WILDCARD_TOKEN, WILDCARD_KEYWORD),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
      PQLToken(PQL_NAME_TOKEN, SUCH_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, THAT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, NOT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, FOLLOWS_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, ass1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, ass2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
      PQLToken(PQL_NAME_TOKEN, AND_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, NOT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, PARENTS_STAR_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, while2),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, ass2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")"),
      PQLToken(PQL_NAME_TOKEN, AND_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, NOT_KEYWORD),
      PQLToken(PQL_NAME_TOKEN, PARENTS_STAR_ABSTRACTION),
      PQLToken(PQL_OPEN_BRACKET_TOKEN, "("),
      PQLToken(PQL_NAME_TOKEN, while1),
      PQLToken(PQL_COMMA_TOKEN, ","),
      PQLToken(PQL_NAME_TOKEN, while2),
      PQLToken(PQL_CLOSE_BRACKET_TOKEN, ")")};

  std::unique_ptr<Query> query =
      parseToQuery(tokenList);

  // expected query object
  Query expected{};

  vector<unique_ptr<SynonymArg>> synonymsToSelect = {};
  synonymsToSelect.push_back(std::make_unique<SynonymArg>(ass2, ASSIGN_ENTITY));
  expected.setSynonymToQuery(std::move(synonymsToSelect));

  // pattern a1 ("x", _)
  unique_ptr<SynonymArg> outerSyn1 =
      std::make_unique<SynonymArg>(ass1, ASSIGN_ENTITY);
  unique_ptr<Ident> firstArg1 = std::make_unique<Ident>("x");
  unique_ptr<Wildcard> secondArg1 = std::make_unique<Wildcard>();
  unique_ptr<AssignPatternClause> patternClause1 =
      std::make_unique<AssignPatternClause>(std::move(outerSyn1),
                                            std::move(firstArg1),
                                            std::move(secondArg1), false);
  expected.addClause(std::move(patternClause1));

  // pattern a2 ("x", _"x"_)
  unique_ptr<SynonymArg> outerSyn2 =
      std::make_unique<SynonymArg>(ass2, ASSIGN_ENTITY);
  unique_ptr<Ident> firstArg2 = std::make_unique<Ident>("x");
  unique_ptr<PatternExp> secondArg2 = std::make_unique<PatternExp>("x");
  unique_ptr<AssignPatternClause> patternClause2 =
      std::make_unique<AssignPatternClause>(std::move(outerSyn2),
                                            std::move(firstArg2),
                                            std::move(secondArg2), true);
  expected.addClause(std::move(patternClause2));

  // Follows (a1, a2)
  unique_ptr<SynonymArg> firstArg3 =
      std::make_unique<SynonymArg>(ass1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> secondArg3 =
      std::make_unique<SynonymArg>(ass2, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause1 = std::make_unique<SuchThatClause>(
      FOLLOWS_ENUM, std::move(firstArg3), std::move(secondArg3));
  expected.addClause(std::move(suchThatClause1));

  // Parent* (w1, a2)
  unique_ptr<SynonymArg> firstArg4 =
      std::make_unique<SynonymArg>(while2, WHILE_ENTITY);
  unique_ptr<SynonymArg> secondArg4 =
      std::make_unique<SynonymArg>(ass2, ASSIGN_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause4 = std::make_unique<SuchThatClause>(
      PARENTS_STAR_ENUM, std::move(firstArg4), std::move(secondArg4));
  expected.addClause(std::move(suchThatClause4));

  // Parent* (w1, w2)
  unique_ptr<SynonymArg> firstArg5 =
      std::make_unique<SynonymArg>(while1, WHILE_ENTITY);
  unique_ptr<SynonymArg> secondArg5 =
      std::make_unique<SynonymArg>(while2, WHILE_ENTITY);
  unique_ptr<SuchThatClause> suchThatClause5 = std::make_unique<SuchThatClause>(
      PARENTS_STAR_ENUM, std::move(firstArg5), std::move(secondArg5));
  expected.addClause(std::move(suchThatClause5));

  bool res = *query == expected;
  REQUIRE(res);
}
