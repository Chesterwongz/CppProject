#include <catch.hpp>

#include "IfEvaluatorTestData.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/common/Keywords.h"
#include "qps/patternEvaluator/ifEvaluator/IfEvaluator.h"

using std::make_unique;

TEST_CASE("test_ifEvaluator_processArgs_synonymFirstArg") {
  ifMockPKBReader.mockIfPattern = mockIfPatternStmtsSynonym;

  // if woof; variable test; select woof pattern woof (test, _ , _ );
  SynonymArg patternSynonym = SynonymArg(ifSynonymValue, IF_ENTITY);
  SynonymArg variableSynonym = SynonymArg("test", VARIABLE_ENTITY);

  unique_ptr<SynonymArg> variableSynonymPtr =
      make_unique<SynonymArg>(variableSynonym.getValue(), VARIABLE_ENTITY);

  IfEvaluator ifEvaluator =
      IfEvaluator(std::move(variableSynonymPtr), ifMockPKBReader,
                  patternSynonym.getValue());

  vector<pair<string, string>> pkbResult = ifEvaluator.evaluateArguments();

  REQUIRE(pkbResult == mockIfPatternStmtsSynonym);
}

TEST_CASE("test_ifEvaluator_processArgs_identFirstArg") {
  ifMockPKBReader.mockIfPattern = mockIfPatternStmtsIdent;

  // if woof; variable test; select woof pattern woof ("a", _ , _ );
  SynonymArg patternSynonym = SynonymArg(ifSynonymValue, IF_ENTITY);
  Ident patternFirstArg = Ident("a");

  unique_ptr<Ident> patternFirstArgPtr =
      make_unique<Ident>(patternFirstArg.getValue());

  IfEvaluator ifEvaluator =
      IfEvaluator(std::move(patternFirstArgPtr), ifMockPKBReader,
                  patternSynonym.getValue());

  vector<pair<string, string>> pkbResult = ifEvaluator.evaluateArguments();

  REQUIRE(pkbResult == mockIfPatternStmtsIdent);
}

TEST_CASE("test_ifEvaluator_processArgs_wildcardFirstArg") {
  // wildcard first arg is the same as variable synonym first arg

  ifMockPKBReader.mockIfPattern = mockIfPatternStmtsSynonym;

  // if woof; select woof pattern woof (_, _ , _ );
  SynonymArg patternSynonym = SynonymArg(ifSynonymValue, IF_ENTITY);

  unique_ptr<Wildcard> wildcardPtr = make_unique<Wildcard>();

  IfEvaluator ifEvaluator = IfEvaluator(std::move(wildcardPtr), ifMockPKBReader,
                                        patternSynonym.getValue());

  vector<pair<string, string>> pkbResult = ifEvaluator.evaluateArguments();

  REQUIRE(pkbResult == mockIfPatternStmtsSynonym);
}

TEST_CASE("test_ifEvaluator_evaluate_synonymFirstArg") {
  ifMockPKBReader.mockIfPattern = mockIfPatternStmtsSynonym;

  // if woof; variable test; select woof pattern woof (test, _ , _ );
  SynonymArg patternSynonym = SynonymArg(ifSynonymValue, IF_ENTITY);
  SynonymArg variableSynonym = SynonymArg("test", VARIABLE_ENTITY);

  unique_ptr<SynonymArg> variableSynonymPtr =
      make_unique<SynonymArg>(variableSynonym.getValue(), VARIABLE_ENTITY);

  IfEvaluator ifEvaluator =
      IfEvaluator(std::move(variableSynonymPtr), ifMockPKBReader,
                  patternSynonym.getValue());

  IntermediateTable actualTable = ifEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getDataAsStrings();

  REQUIRE(actualColNames.size() == 2);
  REQUIRE(actualColNames[0] == patternSynonym.getValue());
  REQUIRE(actualColNames[1] == variableSynonym.getValue());
  REQUIRE(actualTableData.size() == 3);
  REQUIRE(actualTableData[0][0] == mockIfPatternStmtsSynonym[0].first);
  REQUIRE(actualTableData[1][0] == mockIfPatternStmtsSynonym[1].first);
  REQUIRE(actualTableData[2][0] == mockIfPatternStmtsSynonym[2].first);
  REQUIRE(actualTableData[0][1] == mockIfPatternStmtsSynonym[0].second);
  REQUIRE(actualTableData[1][1] == mockIfPatternStmtsSynonym[1].second);
  REQUIRE(actualTableData[2][1] == mockIfPatternStmtsSynonym[2].second);
}

TEST_CASE("test_ifEvaluator_evaluate_identFirstArg") {
  ifMockPKBReader.mockIfPattern = mockIfPatternStmtsIdent;

  // if woof; variable test; select woof pattern woof ("a", _ , _ );
  SynonymArg patternSynonym = SynonymArg(ifSynonymValue, IF_ENTITY);
  Ident patternFirstArg = Ident("a");

  unique_ptr<Ident> patternFirstArgPtr =
      make_unique<Ident>(patternFirstArg.getValue());

  IfEvaluator ifEvaluator =
      IfEvaluator(std::move(patternFirstArgPtr), ifMockPKBReader,
                  patternSynonym.getValue());

  IntermediateTable actualTable = ifEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getDataAsStrings();

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == patternSynonym.getValue());
  REQUIRE(actualTableData.size() == 1);
  REQUIRE(actualTableData[0][0] == mockIfPatternStmtsIdent[0].first);
}

TEST_CASE("test_ifEvaluator_evaluate_wildcardFirstArg") {
  // wildcard first arg is the same is variable synonym first arg
  // but without the variable column in the result
  // only selected synonym will be in the result column

  ifMockPKBReader.mockIfPattern = mockIfPatternStmtsSynonym;

  // if woof; variable test; select woof pattern woof (test, _ , _ );
  SynonymArg patternSynonym = SynonymArg(ifSynonymValue, IF_ENTITY);

  unique_ptr<Wildcard> wildcardPtr = make_unique<Wildcard>();

  IfEvaluator ifEvaluator = IfEvaluator(std::move(wildcardPtr), ifMockPKBReader,
                                        patternSynonym.getValue());

  IntermediateTable actualTable = ifEvaluator.evaluate();

  vector<string> actualColNames = actualTable.getColNames();
  vector<vector<string>> actualTableData = actualTable.getDataAsStrings();

  REQUIRE(actualColNames.size() == 1);
  REQUIRE(actualColNames[0] == patternSynonym.getValue());
  REQUIRE(actualTableData.size() == 3);
  REQUIRE(actualTableData[0][0] == mockIfPatternStmtsSynonym[0].first);
  REQUIRE(actualTableData[1][0] == mockIfPatternStmtsSynonym[1].first);
  REQUIRE(actualTableData[2][0] == mockIfPatternStmtsSynonym[2].first);
}
