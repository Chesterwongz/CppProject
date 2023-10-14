#include <catch.hpp>

#include "../../unit_testing/src/qps/mocks/MockContext.h"
#include "../../unit_testing/src/qps/mocks/MockPKBReader.h"
#include "qps/argument/ident/Ident.h"
#include "qps/argument/patternExp/PatternExp.h"
#include "qps/clause/patternClause/AssignPatternClause.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/common/Keywords.h"

using std::unique_ptr, std::make_unique;

TEST_CASE("test_assignPatternClause_isEqual") {
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

  AssignPatternClause patternClause1 = AssignPatternClause(
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

  AssignPatternClause patternClause2 = AssignPatternClause(
      std::move(patternSynonymPtr2), std::move(patternArgsStreamTest2), false);

  REQUIRE(patternClause1.isEquals(patternClause2));
  REQUIRE(patternClause2.isEquals(patternClause1));
}

TEST_CASE("test_assignPatternClause_evaluate_synonymFirstArg") {
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

  AssignPatternClause patternClause = AssignPatternClause(
      std::move(patternSynonymPtr), std::move(patternArgsStreamTest), false);

  PKBStorage pkbStorage = PKBStorage();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStorage);

  mockPkbReader.resetMockExactAssignPatternStmts();
  mockPkbReader.resetMockPartialAssignPatternStmts();

  vector<string> mockExactAssignPatternStmts = {"1", "2", "3"};
  mockPkbReader.mockExactAssignPattern = mockExactAssignPatternStmts;
  vector<pair<string, string>> mockModifiedPairs = {
      {"1", "a"}, {"3", "b"}, {"5", "c"}};
  mockPkbReader.mockAllModifiedVariables = mockModifiedPairs;

  MockContext mockContext = MockContext();
  mockContext.mockTokenEntity = ASSIGN_ENTITY;

  IntermediateTable actualTable =
      patternClause.evaluate(mockContext, mockPkbReader);
  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getData();
  vector<vector<string>> expectedData = {{"1", "a"}, {"3", "b"}};

  REQUIRE(actualColNames.size() == 2);
  REQUIRE(actualColNames[1] == firstArg.getValue());
  REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_assignPatternClause_evaluate_identFirstArg") {
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

  AssignPatternClause patternClause = AssignPatternClause(
      std::move(patternSynonymPtr), std::move(patternArgsStreamTest), false);

  PKBStorage pkbStorage = PKBStorage();
  MockPKBReader mockPkbReader = MockPKBReader(pkbStorage);

  mockPkbReader.resetMockExactAssignPatternStmts();
  mockPkbReader.resetMockPartialAssignPatternStmts();

  vector<string> mockExactAssignPatternStmts = {"3"};
  mockPkbReader.mockExactAssignPattern = mockExactAssignPatternStmts;
  vector<pair<string, string>> mockModifiedPairs = {
      {"1", "a"}, {"3", "b"}, {"5", "c"}};
  mockPkbReader.mockAllModifiedVariables = mockModifiedPairs;

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
