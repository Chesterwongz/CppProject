#include "catch.hpp"

#include "qps/patternEvaluator/assignEvaluator/AssignEvaluator.h"
#include "../../patternEvaluator/assignEvaluator/AssignEvaluatorTestData.h"
#include "qps/common/Keywords.h"

using std::make_unique;

TEST_CASE("test_AssignEvaluator_processArgs_synonymFirstArg") {
	assignMockPKBReader.resetMockExactAssignPatternStmts();
	assignMockPKBReader.resetMockPartialAssignPatternStmts();
	assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmts;

	// assign meow; variable test; select meow pattern (test, "x");
	SynonymArg selectedSynonym = SynonymArg(assignSynonymValue);
	SynonymArg variableSynonym = SynonymArg("test");
	Ident ident = Ident("x");

	unique_ptr<SynonymArg> variableSynonymPtr = make_unique<SynonymArg>(variableSynonym.getValue());
	unique_ptr<Ident> identPtr = make_unique<Ident>(ident.getValue());

	PatternArgsStream patternArgsStreamTest;
	patternArgsStreamTest.push_back(std::move(variableSynonymPtr));
	patternArgsStreamTest.push_back(std::move(identPtr));

	AssignEvaluator assignEvaluator = AssignEvaluator(
		assignMockContext,
		patternArgsStreamTest,
		assignMockPKBReader,
		assignIsPartialMatchFalse,
		selectedSynonym.getValue());

	vector<string> pkbResult = assignEvaluator.processArguments();

	REQUIRE(pkbResult == mockExactAssignPatternStmts);

}

TEST_CASE("test_AssignEvaluator_processArgs_identFirstArg") {
	assignMockPKBReader.resetMockExactAssignPatternStmts();
	assignMockPKBReader.resetMockPartialAssignPatternStmts();
	assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmtsIdent;
	assignMockPKBReader.mockAllModifiedVariables = mockAllModifiedVariables;

	// assign meow; select meow pattern ("a", "x");
	SynonymArg selectedSynonym = SynonymArg(assignSynonymValue);
	Ident patternFirstArg = Ident("a");
	Ident patternExp = Ident("x");

	unique_ptr<Ident> patternFirstArgPtr = make_unique<Ident>(patternFirstArg.getValue());
	unique_ptr<Ident> patternExpPtr = make_unique<Ident>(patternExp.getValue());

	PatternArgsStream patternArgsStreamTest;
	patternArgsStreamTest.push_back(std::move(patternFirstArgPtr));
	patternArgsStreamTest.push_back(std::move(patternExpPtr));

	AssignEvaluator assignEvaluator = AssignEvaluator(
		assignMockContext,
		patternArgsStreamTest,
		assignMockPKBReader,
		assignIsPartialMatchFalse,
		selectedSynonym.getValue());

	vector<string> pkbResult = assignEvaluator.processArguments();

	REQUIRE(pkbResult == mockExactAssignPatternStmtsIdent);

}

TEST_CASE("test_AssignEvaluator_evaluate_synonymFirstArg") {
	assignMockPKBReader.resetMockExactAssignPatternStmts();
	assignMockPKBReader.resetMockPartialAssignPatternStmts();
	assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmts;
	assignMockPKBReader.mockAllModifiedVariables = mockAllModifiedVariables;

	// assign meow; variable test; select meow pattern (test, "x");
	SynonymArg selectedSynonym = SynonymArg(assignSynonymValue);
	SynonymArg variableSynonym = SynonymArg("test");
	Ident ident = Ident("x");

	unique_ptr<SynonymArg> variableSynonymPtr = make_unique<SynonymArg>(variableSynonym.getValue());
	unique_ptr<Ident> identPtr = make_unique<Ident>(ident.getValue());

	PatternArgsStream patternArgsStreamTest;
	patternArgsStreamTest.push_back(std::move(variableSynonymPtr));
	patternArgsStreamTest.push_back(std::move(identPtr));

	AssignEvaluator assignEvaluator = AssignEvaluator(
		assignMockContext,
		patternArgsStreamTest,
		assignMockPKBReader,
		assignIsPartialMatchFalse,
		selectedSynonym.getValue());

	IntermediateTable actualTable = assignEvaluator.evaluate();

	vector<string> actualColNames = actualTable.getColNames();
	vector<vector<string>> actualTableData = actualTable.getData();

	REQUIRE(actualColNames.size() == 2);
	REQUIRE(actualColNames[0] == selectedSynonym.getValue());
	REQUIRE(actualColNames[1] == variableSynonym.getValue());
	REQUIRE(actualTableData.size() == 3);
	REQUIRE(actualTableData[0][0] == mockExactAssignPatternStmts[0]);
	REQUIRE(actualTableData[1][0] == mockExactAssignPatternStmts[1]);
	REQUIRE(actualTableData[2][0] == mockExactAssignPatternStmts[2]);
	REQUIRE(actualTableData[0][1] == mockAllModifiedVariables[0].second);
	REQUIRE(actualTableData[1][1] == mockAllModifiedVariables[1].second);
	REQUIRE(actualTableData[2][1] == mockAllModifiedVariables[2].second);
}

TEST_CASE("test_AssignEvaluator_evaluate_identFirstArg") {
	assignMockPKBReader.resetMockExactAssignPatternStmts();
	assignMockPKBReader.resetMockPartialAssignPatternStmts();
	assignMockPKBReader.mockExactAssignPattern = mockExactAssignPatternStmtsIdent;
	assignMockPKBReader.mockAllModifiedVariables = mockAllModifiedVariables;

	// assign meow; select meow pattern ("a", "x");
	SynonymArg selectedSynonym = SynonymArg(assignSynonymValue);
	Ident patternFirstArg = Ident("a");
	Ident patternExp = Ident("x");

	unique_ptr<Ident> patternFirstArgPtr = make_unique<Ident>(patternFirstArg.getValue());
	unique_ptr<Ident> patternExpPtr = make_unique<Ident>(patternExp.getValue());

	PatternArgsStream patternArgsStreamTest;
	patternArgsStreamTest.push_back(std::move(patternFirstArgPtr));
	patternArgsStreamTest.push_back(std::move(patternExpPtr));

	AssignEvaluator assignEvaluator = AssignEvaluator(
		assignMockContext,
		patternArgsStreamTest,
		assignMockPKBReader,
		assignIsPartialMatchFalse,
		selectedSynonym.getValue());

	IntermediateTable actualTable = assignEvaluator.evaluate();

	vector<string> actualColNames = actualTable.getColNames();
	vector<vector<string>> actualTableData = actualTable.getData();

	REQUIRE(actualColNames.size() == 1);
	REQUIRE(actualColNames[0] == selectedSynonym.getValue());
	REQUIRE(actualTableData.size() == 1);
	REQUIRE(actualTableData[0][0] == mockExactAssignPatternStmts[0]);
}
