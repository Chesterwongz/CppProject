#include <catch.hpp>

#include "../../patternEvaluator/assignEvaluator/AssignEvaluatorTestData.h"
#include "qps/common/Keywords.h"
#include "qps/patternEvaluator/assignEvaluator/AssignEvaluator.h"

using std::make_unique;

TEST_CASE("test_AssignEvaluator_processArgs_synonymFirstArg") {
  assignMockPKBReader.resetMockExactAssignPatternStmts();
  assignMockPKBReader.resetMockPartialAssignPatternStmts();
  assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmts;

  // assign meow; variable test; select meow pattern meow (test, "x");
  SynonymArg selectedSynonym = SynonymArg(assignSynonymValue);
  SynonymArg variableSynonym = SynonymArg("test");
  PatternExp patternExp = PatternExp("x");

  unique_ptr<SynonymArg> variableSynonymPtr =
      make_unique<SynonymArg>(variableSynonym.getValue());
  unique_ptr<PatternExp> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  AssignEvaluator assignEvaluator =
      AssignEvaluator(std::move(variableSynonymPtr), std::move(patternExpPtr),
                      assignMockPKBReader, assignIsPartialMatchFalse,
                      selectedSynonym.getValue());

  vector<pair<string, string>> pkbResult = assignEvaluator.processArguments();

  REQUIRE(pkbResult == mockExactAssignPatternStmts);
}

TEST_CASE("test_AssignEvaluator_processArgs_identFirstArg") {
  assignMockPKBReader.resetMockExactAssignPatternStmts();
  assignMockPKBReader.resetMockPartialAssignPatternStmts();
  assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmtsIdent;
  assignMockPKBReader.mockAllModifiedVariables = mockAllModifiedVariables;

  // assign meow; select meow pattern meow ("a", "x");
  SynonymArg selectedSynonym = SynonymArg(assignSynonymValue);
  Ident patternFirstArg = Ident("a");
  PatternExp patternExp = PatternExp("x");

  unique_ptr<Ident> patternFirstArgPtr =
      make_unique<Ident>(patternFirstArg.getValue());
  unique_ptr<PatternExp> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  AssignEvaluator assignEvaluator =
      AssignEvaluator(std::move(patternFirstArgPtr), std::move(patternExpPtr),
                      assignMockPKBReader, assignIsPartialMatchFalse,
                      selectedSynonym.getValue());

  vector<pair<string, string>> pkbResult = assignEvaluator.processArguments();

  REQUIRE(pkbResult == mockExactAssignPatternStmtsIdent);
}

TEST_CASE("test_AssignEvaluator_processArgs_wildcardFirstArg") {
  // wildcard first arg is the same as variable synonym first arg

  assignMockPKBReader.resetMockExactAssignPatternStmts();
  assignMockPKBReader.resetMockPartialAssignPatternStmts();
  assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmts;

  // assign meow; select meow pattern meow (_, "x");
  SynonymArg selectedSynonym = SynonymArg(assignSynonymValue);
  PatternExp patternExp = PatternExp("x");

  unique_ptr<Wildcard> wildcardPtr = make_unique<Wildcard>();
  unique_ptr<PatternExp> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  AssignEvaluator assignEvaluator = AssignEvaluator(
      std::move(wildcardPtr), std::move(patternExpPtr), assignMockPKBReader,
      assignIsPartialMatchFalse, selectedSynonym.getValue());

  vector<pair<string, string>> pkbResult = assignEvaluator.processArguments();

  REQUIRE(pkbResult == mockExactAssignPatternStmts);
}

TEST_CASE("test_AssignEvaluator_evaluate_synonymFirstArg") {
  assignMockPKBReader.resetMockExactAssignPatternStmts();
  assignMockPKBReader.resetMockPartialAssignPatternStmts();
  assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmts;
  assignMockPKBReader.mockAllModifiedVariables = mockAllModifiedVariables;

  // assign meow; variable test; select meow pattern meow (test, "x");
  SynonymArg selectedSynonym = SynonymArg(assignSynonymValue);
  SynonymArg variableSynonym = SynonymArg("test");
  PatternExp patternExp = PatternExp("x");

  unique_ptr<SynonymArg> variableSynonymPtr =
      make_unique<SynonymArg>(variableSynonym.getValue());
  unique_ptr<PatternExp> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  AssignEvaluator assignEvaluator =
      AssignEvaluator(std::move(variableSynonymPtr), std::move(patternExpPtr),
                      assignMockPKBReader, assignIsPartialMatchFalse,
                      selectedSynonym.getValue());

  IntermediateTable actualTable = assignEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getData();

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
  SynonymArg selectedSynonym = SynonymArg(assignSynonymValue);
  Ident patternFirstArg = Ident("a");
  PatternExp patternExp = PatternExp("x");

  unique_ptr<Ident> patternFirstArgPtr =
      make_unique<Ident>(patternFirstArg.getValue());
  unique_ptr<PatternExp> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  AssignEvaluator assignEvaluator =
      AssignEvaluator(std::move(patternFirstArgPtr), std::move(patternExpPtr),
                      assignMockPKBReader, assignIsPartialMatchFalse,
                      selectedSynonym.getValue());

  IntermediateTable actualTable = assignEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getData();

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
  SynonymArg selectedSynonym = SynonymArg(assignSynonymValue);
  PatternExp patternExp = PatternExp("x");

  unique_ptr<Wildcard> wildcardPtr = make_unique<Wildcard>();
  unique_ptr<PatternExp> patternExpPtr =
      make_unique<PatternExp>(patternExp.getValue());

  AssignEvaluator assignEvaluator = AssignEvaluator(
      std::move(wildcardPtr), std::move(patternExpPtr), assignMockPKBReader,
      assignIsPartialMatchFalse, selectedSynonym.getValue());

  IntermediateTable actualTable = assignEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getData();

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == selectedSynonym.getValue());
  REQUIRE(actualTableData.size() == 3);
  REQUIRE(actualTableData[0][0] == mockExactAssignPatternStmts[0].first);
  REQUIRE(actualTableData[1][0] == mockExactAssignPatternStmts[1].first);
  REQUIRE(actualTableData[2][0] == mockExactAssignPatternStmts[2].first);
}
