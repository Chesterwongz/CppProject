#include <string>
#include <catch.hpp>

#include "../../unit_testing/src/qps/mocks/MockPKBReader.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/patternExp/PatternExp.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/patternClause/WhilePatternClause.h"
#include "qps/common/Keywords.h"

using std::unique_ptr, std::make_unique;

TEST_CASE("test_whilePatternClause_isEqual") {
  string patternSynonym = "a";
  string firstArg = "test";

  unique_ptr<SynonymArg> patternSynonymPtr1 =
      std::make_unique<SynonymArg>(patternSynonym, WHILE_ENTITY);
  unique_ptr<SynonymArg> firstArgPtr1 =
      std::make_unique<SynonymArg>(firstArg, VARIABLE_ENTITY);

  WhilePatternClause patternClause1 = WhilePatternClause(
      std::move(patternSynonymPtr1), std::move(firstArgPtr1));

  unique_ptr<SynonymArg> patternSynonymPtr2 =
      std::make_unique<SynonymArg>(patternSynonym, WHILE_ENTITY);
  unique_ptr<SynonymArg> firstArgPtr2 =
      std::make_unique<SynonymArg>(firstArg, VARIABLE_ENTITY);

  WhilePatternClause patternClause2 = WhilePatternClause(
      std::move(patternSynonymPtr2), std::move(firstArgPtr2));

  REQUIRE(patternClause1.isEquals(patternClause2));
  REQUIRE(patternClause2.isEquals(patternClause1));
}

TEST_CASE("test_whilePatternClause_evaluate_synonymFirstArg") {
  // while w; variable test; select w pattern (test, _)
  string patternSynonym = "a";
  string firstArg = "test";

  unique_ptr<SynonymArg> patternSynonymPtr =
      std::make_unique<SynonymArg>(patternSynonym, IF_ENTITY);
  unique_ptr<SynonymArg> firstArgPtr =
      std::make_unique<SynonymArg>(firstArg, VARIABLE_ENTITY);

  WhilePatternClause patternClause =
      WhilePatternClause(std::move(patternSynonymPtr), std::move(firstArgPtr));

  PKBStorage pkbStorage = PKBStorage();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStorage);

  vector<pair<string, string>> mockWhilePatternStmts = {
      {"1", "a"}, {"3", "b"}, {"5", "c"}};
  mockPkbReader.mockWhilePattern = mockWhilePatternStmts;

  IntermediateTable actualTable = patternClause.evaluate(mockPkbReader);
  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getData();
  vector<vector<string>> expectedData = {{"1", "a"}, {"3", "b"}, {"5", "c"}};

  REQUIRE(actualColNames.size() == 2);
  REQUIRE(actualColNames[1] == firstArg);
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_whilePatternClause_evaluate_identFirstArg") {
  // while w; select w pattern ("b", _)
  string patternSynonym = "a";
  string firstArg = "b";

  unique_ptr<SynonymArg> patternSynonymPtr =
      std::make_unique<SynonymArg>(patternSynonym, WHILE_ENTITY);
  unique_ptr<Ident> firstArgPtr = std::make_unique<Ident>(firstArg);

  WhilePatternClause patternClause =
      WhilePatternClause(std::move(patternSynonymPtr), std::move(firstArgPtr));

  PKBStorage pkbStorage = PKBStorage();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStorage);

  vector<pair<string, string>> mockWhilePatternStmts = {{"3", "b"}};
  mockPkbReader.mockWhilePattern = mockWhilePatternStmts;

  IntermediateTable actualTable = patternClause.evaluate(mockPkbReader);
  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getData();
  vector<vector<string>> expectedData = {{"3"}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == patternSynonym);
  REQUIRE(actualTableData == expectedData);
}
