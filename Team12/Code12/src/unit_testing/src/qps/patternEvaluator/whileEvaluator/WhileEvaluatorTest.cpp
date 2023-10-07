#include <catch.hpp>

#include "qps/patternEvaluator/ifEvaluator/IfEvaluator.h"
#include "qps/common/Keywords.h"
#include "WhileEvaluatorTestData.h"

using std::make_unique;

TEST_CASE("test_whileEvaluator_processArgs_synonymFirstArg") {
  whileMockPKBReader.mockWhilePattern = mockWhilePatternStmtsSynonym;

  // while moo; variable test; select moo pattern moo (test, _);
  SynonymArg patternSynonym = SynonymArg(whileSynonymValue);
  SynonymArg variableSynonym = SynonymArg("test");

  unique_ptr<SynonymArg> variableSynonymPtr =
      make_unique<SynonymArg>(variableSynonym.getValue());

  PatternArgsStream patternArgsStreamTest;
  patternArgsStreamTest.push_back(std::move(variableSynonymPtr));

  IfEvaluator ifEvaluator =
      IfEvaluator(whileMockContext, patternArgsStreamTest, whileMockPKBReader,
                  whileIsPartialMatchFalse, patternSynonym.getValue());

  vector<string> pkbResult = ifEvaluator.processArguments();

  REQUIRE(pkbResult == mockWhilePatternStmtsSynonym);
}

TEST_CASE("test_whileEvaluator_processArgs_identFirstArg") {
  whileMockPKBReader.mockWhilePattern = mockWhilePatternStmtsIdent;

  // if woof; variable test; select woof pattern woof ("a", _ , _ );
  SynonymArg patternSynonym = SynonymArg(whileSynonymValue);
  Ident patternFirstArg = Ident("a");

  unique_ptr<Ident> patternFirstArgPtr =
      make_unique<Ident>(patternFirstArg.getValue());

  PatternArgsStream patternArgsStreamTest;
  patternArgsStreamTest.push_back(std::move(patternFirstArgPtr));

  IfEvaluator ifEvaluator =
      IfEvaluator(whileMockContext, patternArgsStreamTest, whileMockPKBReader,
                  whileIsPartialMatchFalse, patternSynonym.getValue());

  vector<string> pkbResult = ifEvaluator.processArguments();

  REQUIRE(pkbResult == mockWhilePatternStmtsIdent);
}

TEST_CASE("test_whileEvaluator_processArgs_wildcardFirstArg") {
  // wildcard first arg is the same as variable synonym first arg

  whileMockPKBReader.mockWhilePattern = mockWhilePatternStmtsSynonym;

  // if woof; select woof pattern woof (_, _ , _ );
  SynonymArg patternSynonym = SynonymArg(whileSynonymValue);

  unique_ptr<Wildcard> wildcardPtr = make_unique<Wildcard>();

  PatternArgsStream patternArgsStreamTest;
  patternArgsStreamTest.push_back(std::move(wildcardPtr));

  IfEvaluator ifEvaluator =
      IfEvaluator(whileMockContext, patternArgsStreamTest, whileMockPKBReader,
                  whileIsPartialMatchFalse, patternSynonym.getValue());

  vector<string> pkbResult = ifEvaluator.processArguments();

  REQUIRE(pkbResult == mockWhilePatternStmtsSynonym);
}

TEST_CASE("test_whileEvaluator_evaluate_synonymFirstArg") {
  whileMockPKBReader.mockWhilePattern = mockWhilePatternStmtsSynonym;

  // if woof; variable test; select woof pattern woof (test, _ , _ );
  SynonymArg patternSynonym = SynonymArg(whileSynonymValue);
  SynonymArg variableSynonym = SynonymArg("test");

  unique_ptr<SynonymArg> variableSynonymPtr =
      make_unique<SynonymArg>(variableSynonym.getValue());

  PatternArgsStream patternArgsStreamTest;
  patternArgsStreamTest.push_back(std::move(variableSynonymPtr));

  IfEvaluator ifEvaluator =
      IfEvaluator(whileMockContext, patternArgsStreamTest, whileMockPKBReader,
                  whileIsPartialMatchFalse, patternSynonym.getValue());

  IntermediateTable actualTable = ifEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getData();

  REQUIRE(actualColNames.size() == 2);
  REQUIRE(actualColNames[0] == patternSynonym.getValue());
  REQUIRE(actualColNames[1] == variableSynonym.getValue());
  REQUIRE(actualTableData.size() == 3);
  REQUIRE(actualTableData[0][0] == mockWhilePatternStmtsSynonym[0]);
  REQUIRE(actualTableData[1][0] == mockWhilePatternStmtsSynonym[1]);
  REQUIRE(actualTableData[2][0] == mockWhilePatternStmtsSynonym[2]);
  REQUIRE(actualTableData[0][1] == mockAllWhileVariables[0].second);
  REQUIRE(actualTableData[1][1] == mockAllWhileVariables[1].second);
  REQUIRE(actualTableData[2][1] == mockAllWhileVariables[2].second);
}

TEST_CASE("test_whileEvaluator_evaluate_identFirstArg") {
  whileMockPKBReader.mockWhilePattern = mockWhilePatternStmtsIdent;

  // if woof; variable test; select woof pattern woof ("a", _ , _ );
  SynonymArg patternSynonym = SynonymArg(whileSynonymValue);
  Ident patternFirstArg = Ident("a");

  unique_ptr<Ident> patternFirstArgPtr =
      make_unique<Ident>(patternFirstArg.getValue());

  PatternArgsStream patternArgsStreamTest;
  patternArgsStreamTest.push_back(std::move(patternFirstArgPtr));

  IfEvaluator ifEvaluator =
      IfEvaluator(whileMockContext, patternArgsStreamTest, whileMockPKBReader,
                  whileIsPartialMatchFalse, patternSynonym.getValue());

  IntermediateTable actualTable = ifEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getData();

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == patternSynonym.getValue());
  REQUIRE(actualTableData.size() == 1);
  REQUIRE(actualTableData[0][0] == mockWhilePatternStmtsIdent[0]);
}

TEST_CASE("test_whileEvaluator_evaluate_wildcardFirstArg") {
  // wildcard first arg is the same is variable synonym first arg
  // but without the variable column in the result
  // only selected synonym will be in the result column

  whileMockPKBReader.mockWhilePattern = mockWhilePatternStmtsSynonym;

  // if woof; variable test; select woof pattern woof (test, _ , _ );
  SynonymArg patternSynonym = SynonymArg(whileSynonymValue);

  unique_ptr<Wildcard> wildcardPtr = make_unique<Wildcard>();

  PatternArgsStream patternArgsStreamTest;
  patternArgsStreamTest.push_back(std::move(wildcardPtr));

  IfEvaluator ifEvaluator =
      IfEvaluator(whileMockContext, patternArgsStreamTest, whileMockPKBReader,
                  whileIsPartialMatchFalse, patternSynonym.getValue());

  IntermediateTable actualTable = ifEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getData();

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == patternSynonym.getValue());
  REQUIRE(actualTableData.size() == 3);
  REQUIRE(actualTableData[0][0] == mockWhilePatternStmtsSynonym[0]);
  REQUIRE(actualTableData[1][0] == mockWhilePatternStmtsSynonym[1]);
  REQUIRE(actualTableData[2][0] == mockWhilePatternStmtsSynonym[2]);
}
