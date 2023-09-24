#include "catch.hpp"

#include "qps/clause/patternClause/PatternClause.h"
#include "qps/argument/synonymArg/SynonymArg.h"
#include "qps/argument/ident/Ident.h"
#include "../../unit_testing/src/qps/mocks/MockPKBReader.h"
#include "../../unit_testing/src/qps/mocks/MockContext.h"
#include "qps/common/Keywords.h"

using std::unique_ptr, std::make_unique;

TEST_CASE("test_PatternClause_isEqual") {
	SynonymArg patternSynonym = SynonymArg("a");
	SynonymArg firstArg = SynonymArg("test");
	Ident secondArg = Ident("x", PQL_LITERAL_REF_TOKEN);

	unique_ptr<SynonymArg> patternSynonymPtr1 = std::make_unique<SynonymArg>(patternSynonym.getValue());
	unique_ptr<SynonymArg> firstArgPtr1 = std::make_unique<SynonymArg>(firstArg.getValue());
	unique_ptr<Ident>secondArgPtr1 = make_unique<Ident>(secondArg.getValue(), PQL_LITERAL_REF_TOKEN);

	PatternArgsStream patternArgsStreamTest1;
	patternArgsStreamTest1.push_back(std::move(firstArgPtr1));
	patternArgsStreamTest1.push_back(std::move(secondArgPtr1));

	PatternArgsStreamPtr patternArgsStreamPtrTest1 = make_unique<PatternArgsStream>(std::move(patternArgsStreamTest1));

	PatternClause patternClause1 = PatternClause(std::move(patternSynonymPtr1), std::move(patternArgsStreamPtrTest1), false);

	unique_ptr<SynonymArg> patternSynonymPtr2 = std::make_unique<SynonymArg>(patternSynonym.getValue());
	unique_ptr<SynonymArg> firstArgPtr2 = std::make_unique<SynonymArg>(firstArg.getValue());
	unique_ptr<Ident>secondArgPtr2 = make_unique<Ident>(secondArg.getValue(), PQL_LITERAL_REF_TOKEN);

	PatternArgsStream patternArgsStreamTest2;
	patternArgsStreamTest2.push_back(std::move(firstArgPtr2));
	patternArgsStreamTest2.push_back(std::move(secondArgPtr2));

	PatternArgsStreamPtr patternArgsStreamPtrTest2 = make_unique<PatternArgsStream>(std::move(patternArgsStreamTest2));

	PatternClause patternClause2 = PatternClause(std::move(patternSynonymPtr2), std::move(patternArgsStreamPtrTest2), false);

	REQUIRE(patternClause1.isEquals(patternClause2));
	REQUIRE(patternClause2.isEquals(patternClause1));
}

TEST_CASE("test_PatternClause_evaluate") {
	SynonymArg patternSynonym = SynonymArg("a");
	SynonymArg firstArg = SynonymArg("test");
	Ident secondArg = Ident("x", PQL_LITERAL_REF_TOKEN);

	unique_ptr<SynonymArg> patternSynonymPtr = std::make_unique<SynonymArg>(patternSynonym.getValue());
	unique_ptr<SynonymArg> firstArgPtr = std::make_unique<SynonymArg>(firstArg.getValue());
	unique_ptr<Ident>secondArgPtr = make_unique<Ident>(secondArg.getValue(), PQL_LITERAL_REF_TOKEN);

	PatternArgsStream patternArgsStreamTest;
	patternArgsStreamTest.push_back(std::move(firstArgPtr));
	patternArgsStreamTest.push_back(std::move(secondArgPtr));

	PatternArgsStreamPtr patternArgsStreamPtrTest = make_unique<PatternArgsStream>(std::move(patternArgsStreamTest));

	PatternClause patternClause = PatternClause(std::move(patternSynonymPtr), std::move(patternArgsStreamPtrTest), false);

	PKBStorage pkbStorage = PKBStorage();
	MockPKBReader mockPkbReader = MockPKBReader(pkbStorage);

	mockPkbReader.resetMockExactAssignPatternStmts();
	mockPkbReader.resetMockPartialAssignPatternStmts();

	vector<string> mockExactAssignPatternStmts = { "1", "2", "3" };
	mockPkbReader.setMockExactAssignPatternStmts(mockExactAssignPatternStmts);

	MockContext mockContext = MockContext();
	mockContext.mockTokenEntity = ASSIGN_ENTITY;

	IntermediateTable actualTable = patternClause.evaluate(mockContext, mockPkbReader);

	vector<string> actualColNames = actualTable.getColNames();
	vector<vector<string>> actualTableData = actualTable.getData();

	REQUIRE(actualColNames.size() == 1);
	REQUIRE(actualColNames[0] == firstArg.getValue());
	REQUIRE(actualTableData.size() == 3);
	REQUIRE(actualTableData[0][0] == mockExactAssignPatternStmts[0]);
	REQUIRE(actualTableData[1][0] == mockExactAssignPatternStmts[1]);
	REQUIRE(actualTableData[2][0] == mockExactAssignPatternStmts[2]);
}