#include <catch.hpp>

#include "../../unit_testing/src/qps/mocks/MockContext.h"
#include "../../unit_testing/src/qps/mocks/MockPKBReader.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/patternExp/PatternExp.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/clause/patternClause/PatternClause.h"
#include "qps/common/Keywords.h"

using std::unique_ptr, std::make_unique;

TEST_CASE("test_PatternClause_isEqual") {
  SynonymArg patternSynonym = SynonymArg("a");
  SynonymArg firstArg = SynonymArg("test");
  PatternExp secondArg = PatternExp("x");

  unique_ptr<SynonymArg> patternSynonymPtr1 =
      std::make_unique<SynonymArg>(patternSynonym.getValue());
  unique_ptr<SynonymArg> firstArgPtr1 =
      std::make_unique<SynonymArg>(firstArg.getValue());
  unique_ptr<PatternExp> secondArgPtr1 =
      make_unique<PatternExp>(secondArg.getValue());

  PatternArgsStream patternArgsStreamTest1;
  patternArgsStreamTest1.push_back(std::move(firstArgPtr1));
  patternArgsStreamTest1.push_back(std::move(secondArgPtr1));

  PatternClause patternClause1 = PatternClause(
      std::move(patternSynonymPtr1), std::move(patternArgsStreamTest1), false);

  unique_ptr<SynonymArg> patternSynonymPtr2 =
      std::make_unique<SynonymArg>(patternSynonym.getValue());
  unique_ptr<SynonymArg> firstArgPtr2 =
      std::make_unique<SynonymArg>(firstArg.getValue());
  unique_ptr<PatternExp> secondArgPtr2 =
      make_unique<PatternExp>(secondArg.getValue());

  PatternArgsStream patternArgsStreamTest2;
  patternArgsStreamTest2.push_back(std::move(firstArgPtr2));
  patternArgsStreamTest2.push_back(std::move(secondArgPtr2));

  PatternClause patternClause2 = PatternClause(
      std::move(patternSynonymPtr2), std::move(patternArgsStreamTest2), false);

  REQUIRE(patternClause1.isEquals(patternClause2));
  REQUIRE(patternClause2.isEquals(patternClause1));
}

TEST_CASE("test_PatternClause_evaluate_synonymFirstArg") {
  // assign a; variable test; select a pattern (test, "x")
  SynonymArg patternSynonym = SynonymArg("a");
  SynonymArg firstArg = SynonymArg("test");
  PatternExp secondArg = PatternExp("x");

  unique_ptr<SynonymArg> patternSynonymPtr =
      std::make_unique<SynonymArg>(patternSynonym.getValue());
  unique_ptr<SynonymArg> firstArgPtr =
      std::make_unique<SynonymArg>(firstArg.getValue());
  unique_ptr<PatternExp> secondArgPtr =
      make_unique<PatternExp>(secondArg.getValue());

  PatternArgsStream patternArgsStreamTest;
  patternArgsStreamTest.push_back(std::move(firstArgPtr));
  patternArgsStreamTest.push_back(std::move(secondArgPtr));

  PatternClause patternClause = PatternClause(
      std::move(patternSynonymPtr), std::move(patternArgsStreamTest), false);

  PKBStorage pkbStorage = PKBStorage();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStorage);

  mockPkbReader.resetMockExactAssignPatternStmts();
  mockPkbReader.resetMockPartialAssignPatternStmts();

  vector<pair<string, string>> mockExactAssignPatternStmts = {
      make_pair("1", "a"), make_pair("2", "b"), make_pair("3", "c")
  };
  mockPkbReader.mockExactAssignPattern = mockExactAssignPatternStmts;

  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      patternClause.evaluate(mockContext, mockPkbReader);
  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getDataAsStrings();
  vector<vector<string>> expectedData = {{"1", "a"}, {"2", "b"}, {"3", "c"}};

  REQUIRE(actualColNames.size() == 2);
  REQUIRE(actualColNames[1] == firstArg.getValue());
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_PatternClause_evaluate_identFirstArg") {
  // assign a; select a pattern ("b", "x")
  SynonymArg patternSynonym = SynonymArg("a");
  Ident firstArg = Ident("b");
  PatternExp secondArg = PatternExp("x");

  unique_ptr<SynonymArg> patternSynonymPtr =
      std::make_unique<SynonymArg>(patternSynonym.getValue());
  unique_ptr<Ident> firstArgPtr = std::make_unique<Ident>(firstArg.getValue());
  unique_ptr<PatternExp> secondArgPtr =
      make_unique<PatternExp>(secondArg.getValue());

  PatternArgsStream patternArgsStreamTest;
  patternArgsStreamTest.push_back(std::move(firstArgPtr));
  patternArgsStreamTest.push_back(std::move(secondArgPtr));

  PatternClause patternClause = PatternClause(
      std::move(patternSynonymPtr), std::move(patternArgsStreamTest), false);

  PKBStorage pkbStorage = PKBStorage();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStorage);

  mockPkbReader.resetMockExactAssignPatternStmts();
  mockPkbReader.resetMockPartialAssignPatternStmts();

  vector<pair<string, string>> mockExactAssignPatternStmts = {
      make_pair("3", "x")
  };
  mockPkbReader.mockExactAssignPattern = mockExactAssignPatternStmts;

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
