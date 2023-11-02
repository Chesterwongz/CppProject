#include <catch.hpp>

#include "WhileEvaluatorTestData.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/common/Keywords.h"
#include "qps/patternEvaluator/whileEvaluator/WhileEvaluator.h"

using std::make_unique;

TEST_CASE("test_whileEvaluator_processArgs_synonymFirstArg") {
  whileMockPKBReader.mockWhilePattern = mockWhilePatternStmtsSynonym;

  // while moo; variable test; select moo pattern moo (test, _);
  SynonymArg patternSynonym = SynonymArg(whileSynonymValue, WHILE_ENTITY);
  SynonymArg variableSynonym = SynonymArg("test", VARIABLE_ENTITY);

  unique_ptr<AbstractArgument> variableSynonymPtr =
      make_unique<SynonymArg>(variableSynonym.getValue(), VARIABLE_ENTITY);

  WhileEvaluator whileEvaluator =
      WhileEvaluator(variableSynonymPtr, whileMockPKBReader,
                     patternSynonym.getValue());

  vector<pair<string, string>> pkbResult = whileEvaluator.evaluateArguments();

  REQUIRE(pkbResult == mockWhilePatternStmtsSynonym);
}

TEST_CASE("test_whileEvaluator_processArgs_identFirstArg") {
  whileMockPKBReader.mockWhilePattern = mockWhilePatternStmtsIdent;

  // if woof; variable test; select woof pattern woof ("a", _ , _ );
  SynonymArg patternSynonym = SynonymArg(whileSynonymValue, WHILE_ENTITY);
  Ident patternFirstArg = Ident("a");

  unique_ptr<AbstractArgument> patternFirstArgPtr =
      make_unique<Ident>(patternFirstArg.getValue());

  WhileEvaluator whileEvaluator =
      WhileEvaluator(patternFirstArgPtr, whileMockPKBReader,
                     patternSynonym.getValue());

  vector<pair<string, string>> pkbResult = whileEvaluator.evaluateArguments();

  REQUIRE(pkbResult == mockWhilePatternStmtsIdent);
}

TEST_CASE("test_whileEvaluator_processArgs_wildcardFirstArg") {
  // wildcard first arg is the same as variable synonym first arg

  whileMockPKBReader.mockWhilePattern = mockWhilePatternStmtsSynonym;

  // if woof; select woof pattern woof (_, _ , _ );
  SynonymArg patternSynonym = SynonymArg(whileSynonymValue, WHILE_ENTITY);

  unique_ptr<AbstractArgument> wildcardPtr = make_unique<Wildcard>();

  WhileEvaluator whileEvaluator = WhileEvaluator(
      wildcardPtr, whileMockPKBReader, patternSynonym.getValue());

  vector<pair<string, string>> pkbResult = whileEvaluator.evaluateArguments();

  REQUIRE(pkbResult == mockWhilePatternStmtsSynonym);
}

TEST_CASE("test_whileEvaluator_evaluate_synonymFirstArg") {
  whileMockPKBReader.mockWhilePattern = mockWhilePatternStmtsSynonym;

  // if woof; variable test; select woof pattern woof (test, _ , _ );
  SynonymArg patternSynonym = SynonymArg(whileSynonymValue, WHILE_ENTITY);
  SynonymArg variableSynonym = SynonymArg("test", VARIABLE_ENTITY);

  unique_ptr<AbstractArgument> variableSynonymPtr =
      make_unique<SynonymArg>(variableSynonym.getValue(), VARIABLE_ENTITY);

  WhileEvaluator whileEvaluator =
      WhileEvaluator(variableSynonymPtr, whileMockPKBReader,
                     patternSynonym.getValue());

  IntermediateTable actualTable = whileEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getDataAsStrings();

  REQUIRE(actualColNames.size() == 2);
  REQUIRE(actualColNames[0] == patternSynonym.getValue());
  REQUIRE(actualColNames[1] == variableSynonym.getValue());
  REQUIRE(actualTableData.size() == 3);
  REQUIRE(actualTableData[0][0] == mockWhilePatternStmtsSynonym[0].first);
  REQUIRE(actualTableData[1][0] == mockWhilePatternStmtsSynonym[1].first);
  REQUIRE(actualTableData[2][0] == mockWhilePatternStmtsSynonym[2].first);
  REQUIRE(actualTableData[0][1] == mockWhilePatternStmtsSynonym[0].second);
  REQUIRE(actualTableData[1][1] == mockWhilePatternStmtsSynonym[1].second);
  REQUIRE(actualTableData[2][1] == mockWhilePatternStmtsSynonym[2].second);
}

TEST_CASE("test_whileEvaluator_evaluate_identFirstArg") {
  whileMockPKBReader.mockWhilePattern = mockWhilePatternStmtsIdent;

  // if woof; variable test; select woof pattern woof ("a", _ , _ );
  SynonymArg patternSynonym = SynonymArg(whileSynonymValue, WHILE_ENTITY);
  Ident patternFirstArg = Ident("a");

  unique_ptr<AbstractArgument> patternFirstArgPtr =
      make_unique<Ident>(patternFirstArg.getValue());

  WhileEvaluator whileEvaluator =
      WhileEvaluator(patternFirstArgPtr, whileMockPKBReader,
                     patternSynonym.getValue());

  IntermediateTable actualTable = whileEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getDataAsStrings();

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == patternSynonym.getValue());
  REQUIRE(actualTableData.size() == 1);
  REQUIRE(actualTableData[0][0] == mockWhilePatternStmtsIdent[0].first);
}

TEST_CASE("test_whileEvaluator_evaluate_wildcardFirstArg") {
  // wildcard first arg is the same is variable synonym first arg
  // but without the variable column in the result
  // only selected synonym will be in the result column

  whileMockPKBReader.mockWhilePattern = mockWhilePatternStmtsSynonym;

  // if woof; variable test; select woof pattern woof (test, _ , _ );
  SynonymArg patternSynonym = SynonymArg(whileSynonymValue, WHILE_ENTITY);

  unique_ptr<AbstractArgument> wildcardPtr = make_unique<Wildcard>();

  WhileEvaluator whileEvaluator = WhileEvaluator(
      wildcardPtr, whileMockPKBReader, patternSynonym.getValue());

  IntermediateTable actualTable = whileEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getDataAsStrings();

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == patternSynonym.getValue());
  REQUIRE(actualTableData.size() == 3);
  REQUIRE(actualTableData[0][0] == mockWhilePatternStmtsSynonym[0].first);
  REQUIRE(actualTableData[1][0] == mockWhilePatternStmtsSynonym[1].first);
  REQUIRE(actualTableData[2][0] == mockWhilePatternStmtsSynonym[2].first);
}
