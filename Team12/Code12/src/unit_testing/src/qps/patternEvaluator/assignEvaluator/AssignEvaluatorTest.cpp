#include <catch.hpp>

#include "../../patternEvaluator/assignEvaluator/AssignEvaluatorTestData.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/common/Keywords.h"
#include "qps/patternEvaluator/assignEvaluator/AssignEvaluator.h"

using std::make_unique;

TEST_CASE("test_AssignEvaluator_processArgs_synonymFirstArg") {
  assignMockPKBReader.resetMockExactAssignPatternStmts();
  assignMockPKBReader.resetMockPartialAssignPatternStmts();
  assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmts;

  // assign meow; variable test; select meow pattern meow (test, "x");
  SynonymArg selectedSynonym = SynonymArg(assignSynonymValue, ASSIGN_ENTITY);
  SynonymArg variableSynonym = SynonymArg("test", VARIABLE_ENTITY);
  PatternExp patternExp = PatternExp("x");

  unique_ptr<AbstractArgument> variableSynonymPtr =
      make_unique<SynonymArg>(variableSynonym.getValue(), VARIABLE_ENTITY);
  unique_ptr<AbstractArgument> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  AssignEvaluator assignEvaluator =
      AssignEvaluator(variableSynonymPtr, patternExpPtr, assignMockPKBReader,
                      assignIsPartialMatchFalse, selectedSynonym.getValue());

  vector<pair<string, string>> pkbResult = assignEvaluator.evaluateArguments();

  REQUIRE(pkbResult == mockExactAssignPatternStmts);
}

TEST_CASE("test_AssignEvaluator_processArgs_identFirstArg") {
  assignMockPKBReader.resetMockExactAssignPatternStmts();
  assignMockPKBReader.resetMockPartialAssignPatternStmts();
  assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmtsIdent;
  assignMockPKBReader.mockAllModifiedVariables = mockAllModifiedVariables;

  // assign meow; select meow pattern meow ("a", "x");
  SynonymArg selectedSynonym = SynonymArg(assignSynonymValue, ASSIGN_ENTITY);
  Ident patternFirstArg = Ident("a");
  PatternExp patternExp = PatternExp("x");

  unique_ptr<AbstractArgument> patternFirstArgPtr =
      make_unique<Ident>(patternFirstArg.getValue());
  unique_ptr<AbstractArgument> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  AssignEvaluator assignEvaluator =
      AssignEvaluator(patternFirstArgPtr, patternExpPtr, assignMockPKBReader,
                      assignIsPartialMatchFalse, selectedSynonym.getValue());

  vector<pair<string, string>> pkbResult = assignEvaluator.evaluateArguments();

  REQUIRE(pkbResult == mockExactAssignPatternStmtsIdent);
}

TEST_CASE("test_AssignEvaluator_processArgs_wildcardFirstArg") {
  // wildcard first arg is the same as variable synonym first arg

  assignMockPKBReader.resetMockExactAssignPatternStmts();
  assignMockPKBReader.resetMockPartialAssignPatternStmts();
  assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmts;

  // assign meow; select meow pattern meow (_, "x");
  SynonymArg selectedSynonym = SynonymArg(assignSynonymValue, ASSIGN_ENTITY);
  PatternExp patternExp = PatternExp("x");

  unique_ptr<AbstractArgument> wildcardPtr = make_unique<Wildcard>();
  unique_ptr<AbstractArgument> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  AssignEvaluator assignEvaluator =
      AssignEvaluator(wildcardPtr, patternExpPtr, assignMockPKBReader,
                      assignIsPartialMatchFalse, selectedSynonym.getValue());

  vector<pair<string, string>> pkbResult = assignEvaluator.evaluateArguments();

  REQUIRE(pkbResult == mockExactAssignPatternStmts);
}

TEST_CASE("test_AssignEvaluator_evaluate_synonymFirstArg") {
  assignMockPKBReader.resetMockExactAssignPatternStmts();
  assignMockPKBReader.resetMockPartialAssignPatternStmts();
  assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmts;
  assignMockPKBReader.mockAllModifiedVariables = mockAllModifiedVariables;

  // assign meow; variable test; select meow pattern meow (test, "x");
  SynonymArg selectedSynonym = SynonymArg(assignSynonymValue, ASSIGN_ENTITY);
  SynonymArg variableSynonym = SynonymArg("test", VARIABLE_ENTITY);
  PatternExp patternExp = PatternExp("x");

  unique_ptr<AbstractArgument> variableSynonymPtr =
      make_unique<SynonymArg>(variableSynonym.getValue(), VARIABLE_ENTITY);
  unique_ptr<AbstractArgument> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  AssignEvaluator assignEvaluator =
      AssignEvaluator(variableSynonymPtr, patternExpPtr, assignMockPKBReader,
                      assignIsPartialMatchFalse, selectedSynonym.getValue());

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
  assignMockPKBReader.resetMockExactAssignPatternStmts();
  assignMockPKBReader.resetMockPartialAssignPatternStmts();
  assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmtsIdent;
  assignMockPKBReader.mockAllModifiedVariables = mockAllModifiedVariables;

  // assign meow; select meow pattern meow ("a", "x");
  SynonymArg selectedSynonym = SynonymArg(assignSynonymValue, ASSIGN_ENTITY);
  Ident patternFirstArg = Ident("a");
  PatternExp patternExp = PatternExp("x");

  unique_ptr<AbstractArgument> patternFirstArgPtr =
      make_unique<Ident>(patternFirstArg.getValue());
  unique_ptr<AbstractArgument> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  AssignEvaluator assignEvaluator =
      AssignEvaluator(patternFirstArgPtr, patternExpPtr, assignMockPKBReader,
                      assignIsPartialMatchFalse, selectedSynonym.getValue());

  IntermediateTable actualTable = assignEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getDataAsStrings();

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == selectedSynonym.getValue());
  REQUIRE(actualTableData.size() == 1);
  REQUIRE(actualTableData[0][0] == mockExactAssignPatternStmts[0].first);
}

TEST_CASE("test_AssignEvaluator_evaluate_wildcardFirstArg") {
  // wildcard first arg is the same is variable synonym first arg
  // but without the variable column in the result
  // only selected synonym will be in the result column

  assignMockPKBReader.resetMockExactAssignPatternStmts();
  assignMockPKBReader.resetMockPartialAssignPatternStmts();
  assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmts;
  assignMockPKBReader.mockAllModifiedVariables = mockAllModifiedVariables;

  // assign meow; select meow pattern meow (_, "x");
  SynonymArg selectedSynonym = SynonymArg(assignSynonymValue, ASSIGN_ENTITY);
  PatternExp patternExp = PatternExp("x");

  unique_ptr<AbstractArgument> wildcardPtr = make_unique<Wildcard>();
  unique_ptr<AbstractArgument> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  AssignEvaluator assignEvaluator =
      AssignEvaluator(wildcardPtr, patternExpPtr, assignMockPKBReader,
                      assignIsPartialMatchFalse, selectedSynonym.getValue());

  IntermediateTable actualTable = assignEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getDataAsStrings();

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == selectedSynonym.getValue());
  REQUIRE(actualTableData.size() == 3);
  REQUIRE(actualTableData[0][0] == mockExactAssignPatternStmts[0].first);
  REQUIRE(actualTableData[1][0] == mockExactAssignPatternStmts[1].first);
  REQUIRE(actualTableData[2][0] == mockExactAssignPatternStmts[2].first);
}
