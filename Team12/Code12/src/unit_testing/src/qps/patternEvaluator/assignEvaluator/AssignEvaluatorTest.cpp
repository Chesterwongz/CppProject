#include "catch.hpp"

#include "qps/patternEvaluator/assignEvaluator/AssignEvaluator.h"
#include "../../patternEvaluator/assignEvaluator/AssignEvaluatorTestData.h"

using std::make_unique;

TEST_CASE("test_AssignEvaluator_evaluate") {
	mockPKBReader.resetMockExactAssignPatternStmts();
	mockPKBReader.resetMockPartialAssignPatternStmts();
	mockPKBReader.setMockExactAssignPatternStmts(mockExactAssignPatternStmts);
	
	SynonymArg synonym = SynonymArg("test");
	Ident ident = Ident("x");

	unique_ptr<SynonymArg> synonymPtr = make_unique<SynonymArg>(synonym.getValue());
	unique_ptr<Ident> identPtr = make_unique<Ident>(ident.getValue());

	PatternArgsStream patternArgsStreamTest;
	patternArgsStreamTest.push_back(std::move(synonymPtr));
	patternArgsStreamTest.push_back(std::move(identPtr));

	PatternArgsStreamPtr patternArgsStreamPtrTest = make_unique<PatternArgsStream>(std::move(patternArgsStreamTest));

	AssignEvaluator assignEvaluator = AssignEvaluator(
		mockContext,
		std::move(patternArgsStreamPtrTest),
		mockPKBReader,
		isPartialMatchFalse
	);

	IntermediateTable actualTable = assignEvaluator.evaluate();

	vector<string> actualColNames = actualTable.getColNames();
	vector<vector<string>> actualTableData = actualTable.getData();

	REQUIRE(actualColNames.size() == 1);
	REQUIRE(actualColNames[0] == synonym.getValue());
	REQUIRE(actualTableData.size() == 3);
	REQUIRE(actualTableData[0][0] == mockExactAssignPatternStmts[0]);
	REQUIRE(actualTableData[1][0] == mockExactAssignPatternStmts[1]);
	REQUIRE(actualTableData[2][0] == mockExactAssignPatternStmts[2]);
}