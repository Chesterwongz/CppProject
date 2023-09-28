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
	Ident secondArg = Ident("x");

	unique_ptr<SynonymArg> patternSynonymPtr1 = std::make_unique<SynonymArg>(patternSynonym.getValue());
	unique_ptr<SynonymArg> firstArgPtr1 = std::make_unique<SynonymArg>(firstArg.getValue());
	unique_ptr<Ident>secondArgPtr1 = make_unique<Ident>(secondArg.getValue());

	PatternArgsStream patternArgsStreamTest1;
	patternArgsStreamTest1.push_back(std::move(firstArgPtr1));
	patternArgsStreamTest1.push_back(std::move(secondArgPtr1));

	PatternClause patternClause1 = PatternClause(std::move(patternSynonymPtr1), patternArgsStreamTest1, false);

	unique_ptr<SynonymArg> patternSynonymPtr2 = std::make_unique<SynonymArg>(patternSynonym.getValue());
	unique_ptr<SynonymArg> firstArgPtr2 = std::make_unique<SynonymArg>(firstArg.getValue());
	unique_ptr<Ident>secondArgPtr2 = make_unique<Ident>(secondArg.getValue());

	PatternArgsStream patternArgsStreamTest2;
	patternArgsStreamTest2.push_back(std::move(firstArgPtr2));
	patternArgsStreamTest2.push_back(std::move(secondArgPtr2));

	PatternClause patternClause2 = PatternClause(std::move(patternSynonymPtr2), patternArgsStreamTest2, false);

	REQUIRE(patternClause1.isEquals(patternClause2));
	REQUIRE(patternClause2.isEquals(patternClause1));
}

TEST_CASE("test_PatternClause_evaluate_synonymFirstArg") {
	// assign a; variable test; select a pattern (test, "x")
	SynonymArg patternSynonym = SynonymArg("a");
	SynonymArg firstArg = SynonymArg("test");
	Ident secondArg = Ident("x");

	unique_ptr<SynonymArg> patternSynonymPtr = std::make_unique<SynonymArg>(patternSynonym.getValue());
	unique_ptr<SynonymArg> firstArgPtr = std::make_unique<SynonymArg>(firstArg.getValue());
	unique_ptr<Ident>secondArgPtr = make_unique<Ident>(secondArg.getValue());

	PatternArgsStream patternArgsStreamTest;
	patternArgsStreamTest.push_back(std::move(firstArgPtr));
	patternArgsStreamTest.push_back(std::move(secondArgPtr));

	PatternClause patternClause = PatternClause(std::move(patternSynonymPtr), patternArgsStreamTest, false);

	PKBStorage pkbStorage = PKBStorage();
	MockPKBReader mockPkbReader = MockPKBReader(pkbStorage);

	mockPkbReader.resetMockExactAssignPatternStmts();
	mockPkbReader.resetMockPartialAssignPatternStmts();

	vector<string> mockExactAssignPatternStmts = { "1", "2", "3" };
	mockPkbReader.mockExactAssignPatternStmts = mockExactAssignPatternStmts;
	vector<pair<string,string>> mockModifiedPairs = {{"1", "a"},
													 {"3", "b"},
													 {"5", "c"}};
	mockPkbReader.mockAllModifiedVariables = mockModifiedPairs;

	MockContext mockContext = MockContext();
	mockContext.mockTokenEntity = ASSIGN_ENTITY;

	IntermediateTable actualTable = patternClause.evaluate(mockContext, mockPkbReader);
	vector<string> actualColNames = actualTable.getColNames();
	vector<vector<string>> actualTableData = actualTable.getData();
	vector<vector<string>> expectedData = {{"1", "a"},
											  {"3", "b"}};

	REQUIRE(actualColNames.size() == 2);
	REQUIRE(actualColNames[1] == firstArg.getValue());
	REQUIRE(actualTableData == expectedData);
}

TEST_CASE("test_PatternClause_evaluate_identFirstArg") {
	// assign a; select a pattern ("b", "x")
	SynonymArg patternSynonym = SynonymArg("a");
	Ident firstArg = Ident("b");
	Ident secondArg = Ident("x");

	unique_ptr<SynonymArg> patternSynonymPtr = std::make_unique<SynonymArg>(patternSynonym.getValue());
	unique_ptr<Ident> firstArgPtr = std::make_unique<Ident>(firstArg.getValue());
	unique_ptr<Ident>secondArgPtr = make_unique<Ident>(secondArg.getValue());

	PatternArgsStream patternArgsStreamTest;
	patternArgsStreamTest.push_back(std::move(firstArgPtr));
	patternArgsStreamTest.push_back(std::move(secondArgPtr));

	PatternClause patternClause = PatternClause(std::move(patternSynonymPtr), patternArgsStreamTest, false);

	PKBStorage pkbStorage = PKBStorage();
	MockPKBReader mockPkbReader = MockPKBReader(pkbStorage);

	mockPkbReader.resetMockExactAssignPatternStmts();
	mockPkbReader.resetMockPartialAssignPatternStmts();

	vector<string> mockExactAssignPatternStmts = { "3" };
	mockPkbReader.mockExactAssignPatternStmts = mockExactAssignPatternStmts;
	vector<pair<string, string>> mockModifiedPairs = { {"1", "a"},
													 {"3", "b"},
													 {"5", "c"} };
	mockPkbReader.mockAllModifiedVariables = mockModifiedPairs;

	MockContext mockContext = MockContext();
	mockContext.mockTokenEntity = ASSIGN_ENTITY;

	IntermediateTable actualTable = patternClause.evaluate(mockContext, mockPkbReader);
	vector<string> actualColNames = actualTable.getColNames();
	vector<vector<string>> actualTableData = actualTable.getData();
	vector<vector<string>> expectedData = { {"3"} };

	REQUIRE(actualColNames.size() == 1);
	REQUIRE(actualColNames[0] == patternSynonym.getValue());
	REQUIRE(actualTableData == expectedData);
}
