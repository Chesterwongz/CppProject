#include <catch.hpp>

#include "../../mocks/MockPKBReaderData.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/integer/Integer.h"
#include "qps/argument/patternExp/PatternExp.h"
#include "qps/argument/wildcard/Wildcard.h"
#include "qps/clause/utils/ClauseUtil.h"

TEST_CASE("getSynonymArgValues - valid synonym") {
  unique_ptr<AbstractArgument> arg1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<AbstractArgument> arg2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  set<string> actual = ClauseUtil::getSynonymArgValues(arg1, arg2);
  set<string> expected = {MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2};
  REQUIRE(actual == expected);
}

TEST_CASE("getSynonymArgValues - valid synonym with wildcard") {
  unique_ptr<AbstractArgument> arg1 = std::make_unique<Wildcard>();
  unique_ptr<AbstractArgument> arg2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  set<string> actual = ClauseUtil::getSynonymArgValues(arg1, arg2);
  set<string> expected = {MOCK_SYNONYM_VALUE_2};
  REQUIRE(actual == expected);
}

TEST_CASE("getSynonymArgValues - valid synonym with ident") {
  unique_ptr<AbstractArgument> arg1 =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> arg2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  set<string> actual = ClauseUtil::getSynonymArgValues(arg1, arg2);
  set<string> expected = {MOCK_SYNONYM_VALUE_2};
  REQUIRE(actual == expected);
}

TEST_CASE("getSynonymArgValues - valid synonym with integer") {
  unique_ptr<AbstractArgument> arg1 =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> arg2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
  set<string> actual = ClauseUtil::getSynonymArgValues(arg1, arg2);
  set<string> expected = {MOCK_SYNONYM_VALUE_2};
  REQUIRE(actual == expected);
}

TEST_CASE("getSynonymArgValues - no synonym") {
  unique_ptr<AbstractArgument> integerArg =
      std::make_unique<Integer>(MOCK_INTEGER_VALUE_1);
  unique_ptr<AbstractArgument> identArg =
      std::make_unique<Ident>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> patternArg =
      std::make_unique<PatternExp>(MOCK_IDENT_VALUE_1);
  unique_ptr<AbstractArgument> arg1 = std::make_unique<Wildcard>();

  set<string> intWithIdent =
      ClauseUtil::getSynonymArgValues(integerArg, identArg);
  set<string> patternWithWildcard =
      ClauseUtil::getSynonymArgValues(integerArg, identArg);
  set<string> emptySet = {};

  REQUIRE(intWithIdent == emptySet);
  REQUIRE(patternWithWildcard == emptySet);
}
