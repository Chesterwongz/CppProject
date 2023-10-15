#include <catch.hpp>

#include "../../patternEvaluator/assignEvaluator/AssignEvaluatorTestData.h"
#include "qps/common/Keywords.h"
#include "qps/patternEvaluator/assignEvaluator/AssignEvaluator.h"

using std::make_unique;

TEST_CASE("test_AssignEvaluator_evaluate_synonymFirstArg") {
  mockPKBReader.resetMockExactAssignPatternStmts();
  mockPKBReader.resetMockPartialAssignPatternStmts();
  mockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmts;
  mockPKBReader.mockAllModifiedVariables = mockAllModifiedVariables;

  // assign meow; variable test; select meow pattern (test, "x");
  SynonymArg selectedSynonym = SynonymArg(synonymValue);
  SynonymArg variableSynonym = SynonymArg("test");
  PatternExp patternExp = PatternExp("x");

  unique_ptr<SynonymArg> variableSynonymPtr =
      make_unique<SynonymArg>(variableSynonym.getValue());
  unique_ptr<PatternExp> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  PatternArgsStream patternArgsStreamTest;
  patternArgsStreamTest.push_back(std::move(variableSynonymPtr));
  patternArgsStreamTest.push_back(std::move(patternExpPtr));

  AssignEvaluator assignEvaluator =
      AssignEvaluator(mockContext, patternArgsStreamTest, mockPKBReader,
                      isPartialMatchFalse, selectedSynonym.getValue());

  IntermediateTable actualTable = assignEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getDataAsStrings();

  REQUIRE(actualColNames.size() == 2);
  REQUIRE(actualColNames[0] == selectedSynonym.getValue());
  REQUIRE(actualColNames[1] == variableSynonym.getValue());
  REQUIRE(actualTableData.size() == 3);
  REQUIRE(actualTableData[0][0] == mockExactAssignPatternStmts[0].first);
  REQUIRE(actualTableData[1][0] == mockExactAssignPatternStmts[1].first);
  REQUIRE(actualTableData[2][0] == mockExactAssignPatternStmts[2].first);
  REQUIRE(actualTableData[0][1] == mockExactAssignPatternStmts[0].second);
  REQUIRE(actualTableData[1][1] == mockExactAssignPatternStmts[1].second);
  REQUIRE(actualTableData[2][1] == mockExactAssignPatternStmts[2].second);
}

TEST_CASE("test_AssignEvaluator_evaluate_identFirstArg") {
  mockPKBReader.resetMockExactAssignPatternStmts();
  mockPKBReader.resetMockPartialAssignPatternStmts();
  mockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmtsIdent;
  mockPKBReader.mockAllModifiedVariables = mockAllModifiedVariables;

  // assign meow; select meow pattern ("a", "x");
  SynonymArg selectedSynonym = SynonymArg(synonymValue);
  Ident patternFirstArg = Ident("a");
  PatternExp patternExp = PatternExp("x");

  unique_ptr<Ident> patternFirstArgPtr =
      make_unique<Ident>(patternFirstArg.getValue());
  unique_ptr<PatternExp> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  PatternArgsStream patternArgsStreamTest;
  patternArgsStreamTest.push_back(std::move(patternFirstArgPtr));
  patternArgsStreamTest.push_back(std::move(patternExpPtr));

  AssignEvaluator assignEvaluator =
      AssignEvaluator(mockContext, patternArgsStreamTest, mockPKBReader,
                      isPartialMatchFalse, selectedSynonym.getValue());

  IntermediateTable actualTable = assignEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getDataAsStrings();

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == selectedSynonym.getValue());
  REQUIRE(actualTableData.size() == 1);
  REQUIRE(actualTableData[0][0] == mockExactAssignPatternStmts[0].first);
}
