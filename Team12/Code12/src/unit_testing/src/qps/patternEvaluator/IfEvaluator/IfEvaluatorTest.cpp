#include "catch.hpp"

#include "qps/patternEvaluator/ifEvaluator/IfEvaluator.h"
#include "qps/common/Keywords.h"
#include "IfEvaluatorTestData.h"

using std::make_unique;

TEST_CASE("test_ifEvaluator_processArgs_synonymFirstArg") {
	ifMockPKBReader.mockIfPattern = mockIfPatternStmtsSynonym;

	// if woof; variable test; select woof pattern woof (test, _ , _ );
	SynonymArg patternSynonym = SynonymArg(ifSynonymValue);
	SynonymArg variableSynonym = SynonymArg("test");

	unique_ptr<SynonymArg> variableSynonymPtr = make_unique<SynonymArg>(variableSynonym.getValue());

	PatternArgsStream patternArgsStreamTest;
	patternArgsStreamTest.push_back(std::move(variableSynonymPtr));

	IfEvaluator ifEvaluator = IfEvaluator(
		ifMockContext,
		patternArgsStreamTest,
		ifMockPKBReader,
		ifIsPartialMatchFalse,
		patternSynonym.getValue());

	vector<string> pkbResult = ifEvaluator.processArguments();

	REQUIRE(pkbResult == mockIfPatternStmtsSynonym);

}

TEST_CASE("test_ifEvaluator_processArgs_identFirstArg") {
	ifMockPKBReader.mockIfPattern = mockIfPatternStmtsIdent;

	// if woof; variable test; select woof pattern woof ("a", _ , _ );
	SynonymArg patternSynonym = SynonymArg(ifSynonymValue);
	Ident patternFirstArg = Ident("a");

	unique_ptr<Ident> patternFirstArgPtr = make_unique<Ident>(patternFirstArg.getValue());

	PatternArgsStream patternArgsStreamTest;
	patternArgsStreamTest.push_back(std::move(patternFirstArgPtr));

	IfEvaluator ifEvaluator = IfEvaluator(
		ifMockContext,
		patternArgsStreamTest,
		ifMockPKBReader,
		ifIsPartialMatchFalse,
		patternSynonym.getValue());

	vector<string> pkbResult = ifEvaluator.processArguments();

	REQUIRE(pkbResult == mockIfPatternStmtsIdent);

}

TEST_CASE("test_ifEvaluator_evaluate_synonymFirstArg") {
	ifMockPKBReader.mockIfPattern = mockIfPatternStmtsSynonym;

	// if woof; variable test; select woof pattern woof (test, _ , _ );
	SynonymArg patternSynonym = SynonymArg(ifSynonymValue);
	SynonymArg variableSynonym = SynonymArg("test");

	unique_ptr<SynonymArg> variableSynonymPtr = make_unique<SynonymArg>(variableSynonym.getValue());

	PatternArgsStream patternArgsStreamTest;
	patternArgsStreamTest.push_back(std::move(variableSynonymPtr));

	IfEvaluator ifEvaluator = IfEvaluator(
		ifMockContext,
		patternArgsStreamTest,
		ifMockPKBReader,
		ifIsPartialMatchFalse,
		patternSynonym.getValue());

	IntermediateTable actualTable = ifEvaluator.evaluate();

	vector<string> actualColNames = actualTable.getColNames();
	vector<vector<string>> actualTableData = actualTable.getData();

	REQUIRE(actualColNames.size() == 2);
	REQUIRE(actualColNames[0] == patternSynonym.getValue());
	REQUIRE(actualColNames[1] == variableSynonym.getValue());
	REQUIRE(actualTableData.size() == 3);
	REQUIRE(actualTableData[0][0] == mockIfPatternStmtsSynonym[0]);
	REQUIRE(actualTableData[1][0] == mockIfPatternStmtsSynonym[1]);
	REQUIRE(actualTableData[2][0] == mockIfPatternStmtsSynonym[2]);
	REQUIRE(actualTableData[0][1] == mockAllIfVariables[0].second);
	REQUIRE(actualTableData[1][1] == mockAllIfVariables[1].second);
	REQUIRE(actualTableData[2][1] == mockAllIfVariables[2].second);
}

TEST_CASE("test_ifEvaluator_evaluate_identFirstArg") {
	ifMockPKBReader.mockIfPattern = mockIfPatternStmtsIdent;

	// if woof; variable test; select woof pattern woof ("a", _ , _ );
	SynonymArg patternSynonym = SynonymArg(ifSynonymValue);
	Ident patternFirstArg = Ident("a");

	unique_ptr<Ident> patternFirstArgPtr = make_unique<Ident>(patternFirstArg.getValue());

	PatternArgsStream patternArgsStreamTest;
	patternArgsStreamTest.push_back(std::move(patternFirstArgPtr));

	IfEvaluator ifEvaluator = IfEvaluator(
		ifMockContext,
		patternArgsStreamTest,
		ifMockPKBReader,
		ifIsPartialMatchFalse,
		patternSynonym.getValue());

	IntermediateTable actualTable = ifEvaluator.evaluate();

	vector<string> actualColNames = actualTable.getColNames();
	vector<vector<string>> actualTableData = actualTable.getData();

	REQUIRE(actualColNames.size() == 1);
	REQUIRE(actualColNames[0] == patternSynonym.getValue());
	REQUIRE(actualTableData.size() == 1);
	REQUIRE(actualTableData[0][0] == mockIfPatternStmtsIdent[0]);
}
