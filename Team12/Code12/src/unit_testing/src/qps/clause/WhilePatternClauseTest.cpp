#include <catch.hpp>

#include "../../unit_testing/src/qps/mocks/MockContext.h"
#include "../../unit_testing/src/qps/mocks/MockPKBReader.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/patternExp/PatternExp.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/patternClause/WhilePatternClause.h"
#include "qps/common/Keywords.h"

using std::unique_ptr, std::make_unique;

TEST_CASE("test_whilePatternClause_isEqual") {
  SynonymArg patternSynonym = SynonymArg("a");
  SynonymArg firstArg = SynonymArg("test");

  unique_ptr<SynonymArg> patternSynonymPtr1 =
      std::make_unique<SynonymArg>(patternSynonym.getValue());
  unique_ptr<SynonymArg> firstArgPtr1 =
      std::make_unique<SynonymArg>(firstArg.getValue());

  WhilePatternClause patternClause1 = WhilePatternClause(
      std::move(patternSynonymPtr1), std::move(firstArgPtr1));

  unique_ptr<SynonymArg> patternSynonymPtr2 =
      std::make_unique<SynonymArg>(patternSynonym.getValue());
  unique_ptr<SynonymArg> firstArgPtr2 =
      std::make_unique<SynonymArg>(firstArg.getValue());

  WhilePatternClause patternClause2 = WhilePatternClause(
      std::move(patternSynonymPtr2), std::move(firstArgPtr2));

  REQUIRE(patternClause1.isEquals(patternClause2));
  REQUIRE(patternClause2.isEquals(patternClause1));
}

TEST_CASE("test_whilePatternClause_evaluate_synonymFirstArg") {
  // while w; variable test; select w pattern (test, _)
  SynonymArg patternSynonym = SynonymArg("a");
  SynonymArg firstArg = SynonymArg("test");

  unique_ptr<SynonymArg> patternSynonymPtr =
      std::make_unique<SynonymArg>(patternSynonym.getValue());
  unique_ptr<SynonymArg> firstArgPtr =
      std::make_unique<SynonymArg>(firstArg.getValue());

  WhilePatternClause patternClause =
      WhilePatternClause(std::move(patternSynonymPtr), std::move(firstArgPtr));

  PKBStorage pkbStorage = PKBStorage();
  PKBStore pkbStore = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStorage, pkbStore);

  vector<pair<string, string>> mockWhilePatternStmts = {
      {"1", "a"}, {"3", "b"}, {"5", "c"}};
  mockPkbReader.mockWhilePattern = mockWhilePatternStmts;

  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      patternClause.evaluate(mockContext, mockPkbReader);
  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getData();
  vector<vector<string>> expectedData = {{"1", "a"}, {"3", "b"}, {"5", "c"}};

  REQUIRE(actualColNames.size() == 2);
  REQUIRE(actualColNames[1] == firstArg.getValue());
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_whilePatternClause_evaluate_identFirstArg") {
  // while w; select w pattern ("b", _)
  SynonymArg patternSynonym = SynonymArg("a");
  Ident firstArg = Ident("b");

  unique_ptr<SynonymArg> patternSynonymPtr =
      std::make_unique<SynonymArg>(patternSynonym.getValue());
  unique_ptr<Ident> firstArgPtr = std::make_unique<Ident>(firstArg.getValue());

  WhilePatternClause patternClause =
      WhilePatternClause(std::move(patternSynonymPtr), std::move(firstArgPtr));

  PKBStorage pkbStorage = PKBStorage();
  PKBStore store = PKBStore();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStorage, store);

  vector<pair<string, string>> mockWhilePatternStmts = {{"3", "b"}};
  mockPkbReader.mockWhilePattern = mockWhilePatternStmts;

  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      patternClause.evaluate(mockContext, mockPkbReader);
  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getData();
  vector<vector<string>> expectedData = {{"3"}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == patternSynonym.getValue());
  REQUIRE(actualTableData == expectedData);
}
