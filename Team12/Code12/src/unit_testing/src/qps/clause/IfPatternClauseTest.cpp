#include <catch.hpp>

#include "../../unit_testing/src/qps/mocks/MockContext.h"
#include "../../unit_testing/src/qps/mocks/mockReaders/MockPatternsReader.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/patternExp/PatternExp.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/patternClause/IfPatternClause.h"
#include "qps/common/Keywords.h"

using std::unique_ptr, std::make_unique;

TEST_CASE("test_ifPatternClause_isEqual") {
  SynonymArg patternSynonym = SynonymArg("a");
  SynonymArg firstArg = SynonymArg("test");

  unique_ptr<SynonymArg> patternSynonymPtr1 =
      std::make_unique<SynonymArg>(patternSynonym.getValue());
  unique_ptr<SynonymArg> firstArgPtr1 =
      std::make_unique<SynonymArg>(firstArg.getValue());

  IfPatternClause patternClause1 = IfPatternClause(
      std::move(patternSynonymPtr1), std::move(firstArgPtr1));

  unique_ptr<SynonymArg> patternSynonymPtr2 =
      std::make_unique<SynonymArg>(patternSynonym.getValue());
  unique_ptr<SynonymArg> firstArgPtr2 =
      std::make_unique<SynonymArg>(firstArg.getValue());

  IfPatternClause patternClause2 = IfPatternClause(
      std::move(patternSynonymPtr2), std::move(firstArgPtr2));

  REQUIRE(patternClause1.isEquals(patternClause2));
  REQUIRE(patternClause2.isEquals(patternClause1));
}

TEST_CASE("test_ifPatternClause_evaluate_synonymFirstArg") {
  // while w; variable test; select w pattern (test, _)
  SynonymArg patternSynonym = SynonymArg("a");
  SynonymArg firstArg = SynonymArg("test");

  unique_ptr<SynonymArg> patternSynonymPtr =
      std::make_unique<SynonymArg>(patternSynonym.getValue());
  unique_ptr<SynonymArg> firstArgPtr =
      std::make_unique<SynonymArg>(firstArg.getValue());

  IfPatternClause patternClause =
      IfPatternClause(std::move(patternSynonymPtr), std::move(firstArgPtr));

  PKBStore store = PKBStore();

  MockPatternsReader mockPkbReader = MockPatternsReader();

  vector<pair<string, string>> mockIfPatternStmts = {
      {"1", "a"}, {"3", "b"}, {"5", "c"}};
  mockPkbReader.mockIfPattern = mockIfPatternStmts;

  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      patternClause.evaluate(mockContext, mockPkbReader);
  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getDataAsStrings();
  vector<vector<string>> expectedData = {{"1", "a"}, {"3", "b"}, {"5", "c"}};

  REQUIRE(actualColNames.size() == 2);
  REQUIRE(actualColNames[1] == firstArg.getValue());
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_ifPatternClause_evaluate_identFirstArg") {
  // while w; select w pattern ("b", _)
  SynonymArg patternSynonym = SynonymArg("a");
  Ident firstArg = Ident("b");

  unique_ptr<SynonymArg> patternSynonymPtr =
      std::make_unique<SynonymArg>(patternSynonym.getValue());
  unique_ptr<Ident> firstArgPtr = std::make_unique<Ident>(firstArg.getValue());

  IfPatternClause patternClause =
      IfPatternClause(std::move(patternSynonymPtr), std::move(firstArgPtr));

  PKBStore store = PKBStore();

  MockPatternsReader mockPkbReader = MockPatternsReader();

  vector<pair<string, string>> mockIfPatternStmts = {{"3", "b"}};
  mockPkbReader.mockIfPattern = mockIfPatternStmts;

  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      patternClause.evaluate(mockContext, mockPkbReader);
  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getDataAsStrings();
  vector<vector<string>> expectedData = {{"3"}};

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == patternSynonym.getValue());
  REQUIRE(actualTableData == expectedData);
}
