#include "catch.hpp"

#include "qps/clause/selectClause/SelectClause.h"
#include "../../unit_testing/src/qps/mocks/MockPKBReader.h"
#include "qps/common/Keywords.h"
#include "../qps/mocks/MockPKBReaderData.h"
#include "SelectClauseTestData.h"

TEST_CASE("SelectClause - evaluate - assign entity") {
    MockPKBReader mockPKB = MockPKBReader(MOCK_STORAGE);
    mockPKB.mockStatements = MOCK_SELECT_CLAUSE_DATA;
    Context mockContext = Context();
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_1, ASSIGN_ENTITY);
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_2, ASSIGN_ENTITY);
    unique_ptr<IArgument> mockSynonymArg1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockSynonymArg2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);

    SynonymsToSelect mockSynonymsToSelect = {};
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));

    SelectClause selectClause(std::move(mockSynonymsToSelect));
    IntermediateTable result = selectClause.evaluate(mockContext, mockPKB);

    vector<string> singleColName = { MOCK_SYNONYM_VALUE_2 };
    REQUIRE(result.getColumns(singleColName) == MOCK_RESULTS_1_COL);

    vector<string> doubleColName = { MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2 };
    REQUIRE(result.getColumns(doubleColName) == MOCK_RESULTS_2_COL);
}

TEST_CASE("SelectClause - evaluate - constant entity") {
    MockPKBReader mockPKB = MockPKBReader(MOCK_STORAGE);
    mockPKB.mockAllConstants = MOCK_SELECT_CLAUSE_DATA;
    Context mockContext = Context();
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_1, CONSTANT_ENTITY);
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_2, CONSTANT_ENTITY);
    unique_ptr<IArgument> mockSynonymArg1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockSynonymArg2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);

    SynonymsToSelect mockSynonymsToSelect = {};
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));

    SelectClause selectClause(std::move(mockSynonymsToSelect));
    IntermediateTable result = selectClause.evaluate(mockContext, mockPKB);

    vector<string> singleColName = { MOCK_SYNONYM_VALUE_2 };
    REQUIRE(result.getColumns(singleColName) == MOCK_RESULTS_1_COL);

    vector<string> doubleColName = { MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2 };
    REQUIRE(result.getColumns(doubleColName) == MOCK_RESULTS_2_COL);
}

TEST_CASE("SelectClause - evaluate - procedure entity") {
    MockPKBReader mockPKB = MockPKBReader(MOCK_STORAGE);
    mockPKB.mockAllProcedures = MOCK_SELECT_CLAUSE_DATA;
    Context mockContext = Context();
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_2, PROCEDURE_ENTITY);
    unique_ptr<IArgument> mockSynonymArg1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockSynonymArg2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);

    SynonymsToSelect mockSynonymsToSelect = {};
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));

    SelectClause selectClause(std::move(mockSynonymsToSelect));
    IntermediateTable result = selectClause.evaluate(mockContext, mockPKB);

    vector<string> singleColName = { MOCK_SYNONYM_VALUE_2 };
    REQUIRE(result.getColumns(singleColName) == MOCK_RESULTS_1_COL);

    vector<string> doubleColName = { MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2 };
    REQUIRE(result.getColumns(doubleColName) == MOCK_RESULTS_2_COL);
}

TEST_CASE("SelectClause - evaluate - stmt entity") {
    MockPKBReader mockPKB = MockPKBReader(MOCK_STORAGE);
    mockPKB.mockStatements = MOCK_SELECT_CLAUSE_DATA;
    Context mockContext = Context();
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);
    unique_ptr<IArgument> mockSynonymArg1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockSynonymArg2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);

    SynonymsToSelect mockSynonymsToSelect = {};
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));

    SelectClause selectClause(std::move(mockSynonymsToSelect));
    IntermediateTable result = selectClause.evaluate(mockContext, mockPKB);

    vector<string> singleColName = { MOCK_SYNONYM_VALUE_2 };
    REQUIRE(result.getColumns(singleColName) == MOCK_RESULTS_1_COL);

    vector<string> doubleColName = { MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2 };
    REQUIRE(result.getColumns(doubleColName) == MOCK_RESULTS_2_COL);
}

TEST_CASE("SelectClause - evaluate - variable entity") {
    MockPKBReader mockPKB = MockPKBReader(MOCK_STORAGE);
    mockPKB.mockAllVariables = MOCK_SELECT_CLAUSE_DATA;
    Context mockContext = Context();
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_1, VARIABLE_ENTITY);
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_2, VARIABLE_ENTITY);
    unique_ptr<IArgument> mockSynonymArg1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockSynonymArg2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);

    SynonymsToSelect mockSynonymsToSelect = {};
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));

    SelectClause selectClause(std::move(mockSynonymsToSelect));
    IntermediateTable result = selectClause.evaluate(mockContext, mockPKB);

    vector<string> singleColName = { MOCK_SYNONYM_VALUE_2 };
    REQUIRE(result.getColumns(singleColName) == MOCK_RESULTS_1_COL);

    vector<string> doubleColName = { MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2 };
    REQUIRE(result.getColumns(doubleColName) == MOCK_RESULTS_2_COL);
}

TEST_CASE("SelectClause - evaluate - multi entity") {
    MockPKBReader mockPKB = MockPKBReader(MOCK_STORAGE);
    mockPKB.mockAllConstants = MOCK_SELECT_CLAUSE_DATA;
    mockPKB.mockAllProcedures = MOCK_SELECT_CLAUSE_DATA;
    mockPKB.mockStatements = MOCK_SELECT_CLAUSE_DATA;
    mockPKB.mockAllVariables = MOCK_SELECT_CLAUSE_DATA;

    Context mockContext = Context();
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_1, VARIABLE_ENTITY);
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_2, VARIABLE_ENTITY);
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_3, VARIABLE_ENTITY);
    mockContext.addSynonym(MOCK_SYNONYM_VALUE_4, VARIABLE_ENTITY);

    unique_ptr<IArgument> mockSynonymArg1
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_1);
    unique_ptr<IArgument> mockSynonymArg2
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_2);
    unique_ptr<IArgument> mockSynonymArg3
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_3);
    unique_ptr<IArgument> mockSynonymArg4
            = ArgumentFactory::createArgument(MOCK_SYNONYM_VALUE_4);

    SynonymsToSelect mockSynonymsToSelect = {};
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg3));
    mockSynonymsToSelect.push_back(std::move(mockSynonymArg4));

    SelectClause selectClause(std::move(mockSynonymsToSelect));
    IntermediateTable result = selectClause.evaluate(mockContext, mockPKB);

    vector<string> singleColName = { MOCK_SYNONYM_VALUE_2 };
    REQUIRE(result.getColumns(singleColName) == MOCK_RESULTS_1_COL);

    vector<string> doubleColName = { MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2 };
    REQUIRE(result.getColumns(doubleColName) == MOCK_RESULTS_2_COL);

    vector<string> allColName = {
            MOCK_SYNONYM_VALUE_1,
            MOCK_SYNONYM_VALUE_2,
            MOCK_SYNONYM_VALUE_3,
            MOCK_SYNONYM_VALUE_4 };
    REQUIRE(result.getColumns(allColName) == MOCK_ALL_COL);
}
