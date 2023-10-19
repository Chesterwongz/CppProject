#include <catch.hpp>

#include "../qps/mocks/MockPKBReader.h"
#include "../qps/mocks/MockPKBReaderData.h"
#include "../mocks/MockPKBReader.h"
#include "../mocks/MockPKBReaderData.h"
#include "SelectClauseTestData.h"
#include "qps/clause/selectClause/SelectClause.h"
#include "qps/common/Keywords.h"

TEST_CASE("SelectClause - evaluate - no data") {
  MockPKBReader mockPKB = MockPKBReader(MOCK_STORE);
  unique_ptr<SynonymArg> mockSynonymArg1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> mockSynonymArg2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, ASSIGN_ENTITY);

  SynonymsToSelect mockSynonymsToSelect = {};
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));

  SelectClause selectClause(std::move(mockSynonymsToSelect));
  IntermediateTable result = selectClause.evaluate(mockPKB);

  vector<string> singleColName = {MOCK_SYNONYM_VALUE_2};
  REQUIRE(result.getColumns(singleColName) == MOCK_EMPTY_RESULT);

  vector<string> doubleColName = {MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2};
  REQUIRE(result.getColumns(doubleColName) == MOCK_EMPTY_RESULT);
}

TEST_CASE("SelectClause - evaluate - missing col") {
  MockPKBReader mockPKB = MockPKBReader(MOCK_STORE);
  mockPKB.mockStatements = MOCK_SELECT_CLAUSE_DATA;
  unique_ptr<SynonymArg> mockSynonymArg1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> mockSynonymArg2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, ASSIGN_ENTITY);

  SynonymsToSelect mockSynonymsToSelect = {};
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));

  SelectClause selectClause(std::move(mockSynonymsToSelect));
  IntermediateTable result = selectClause.evaluate(mockPKB);

  vector<string> singleColName = {MOCK_SYNONYM_VALUE_4};
  REQUIRE(result.getColumns(singleColName) == MOCK_EMPTY_RESULT);

  vector<string> doubleColName = {MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_4};
  REQUIRE(result.getColumns(doubleColName) == MOCK_EMPTY_RESULT);
}

TEST_CASE("SelectClause - evaluate - assign entity") {
  MockPKBReader mockPKB = MockPKBReader(MOCK_STORE);
  mockPKB.mockStatements = MOCK_SELECT_CLAUSE_DATA;
  unique_ptr<SynonymArg> mockSynonymArg1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, ASSIGN_ENTITY);
  unique_ptr<SynonymArg> mockSynonymArg2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, ASSIGN_ENTITY);

  SynonymsToSelect mockSynonymsToSelect = {};
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));

  SelectClause selectClause(std::move(mockSynonymsToSelect));
  IntermediateTable result = selectClause.evaluate(mockPKB);

  vector<string> singleColName = {MOCK_SYNONYM_VALUE_2};
  REQUIRE(result.getColumns(singleColName) == MOCK_RESULTS_1_COL);

  vector<string> doubleColName = {MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2};
  REQUIRE(result.getColumns(doubleColName) == MOCK_RESULTS_2_COL);
}

TEST_CASE("SelectClause - evaluate - constant entity") {
  MockPKBReader mockPKB = MockPKBReader(MOCK_STORE);
  mockPKB.mockAllConstants = MOCK_SELECT_CLAUSE_DATA;
  unique_ptr<SynonymArg> mockSynonymArg1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, CONSTANT_ENTITY);
  unique_ptr<SynonymArg> mockSynonymArg2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, CONSTANT_ENTITY);

  SynonymsToSelect mockSynonymsToSelect = {};
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));

  SelectClause selectClause(std::move(mockSynonymsToSelect));
  IntermediateTable result = selectClause.evaluate(mockPKB);

  vector<string> singleColName = {MOCK_SYNONYM_VALUE_2};
  REQUIRE(result.getColumns(singleColName) == MOCK_RESULTS_1_COL);

  vector<string> doubleColName = {MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2};
  REQUIRE(result.getColumns(doubleColName) == MOCK_RESULTS_2_COL);
}

TEST_CASE("SelectClause - evaluate - procedure entity") {
  MockPKBReader mockPKB = MockPKBReader(MOCK_STORE);
  mockPKB.mockAllProcedures = MOCK_SELECT_CLAUSE_DATA;
  unique_ptr<SynonymArg> mockSynonymArg1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<SynonymArg> mockSynonymArg2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, PROCEDURE_ENTITY);

  SynonymsToSelect mockSynonymsToSelect = {};
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));

  SelectClause selectClause(std::move(mockSynonymsToSelect));
  IntermediateTable result = selectClause.evaluate(mockPKB);

  vector<string> singleColName = {MOCK_SYNONYM_VALUE_2};
  REQUIRE(result.getColumns(singleColName) == MOCK_RESULTS_1_COL);

  vector<string> doubleColName = {MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2};
  REQUIRE(result.getColumns(doubleColName) == MOCK_RESULTS_2_COL);
}

TEST_CASE("SelectClause - evaluate - stmt entity") {
  MockPKBReader mockPKB = MockPKBReader(MOCK_STORE);
  mockPKB.mockStatements = MOCK_SELECT_CLAUSE_DATA;

  unique_ptr<SynonymArg> mockSynonymArg1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, STMT_ENTITY);
  unique_ptr<SynonymArg> mockSynonymArg2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, STMT_ENTITY);

  SynonymsToSelect mockSynonymsToSelect = {};
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));

  SelectClause selectClause(std::move(mockSynonymsToSelect));
  IntermediateTable result = selectClause.evaluate(mockPKB);

  vector<string> singleColName = {MOCK_SYNONYM_VALUE_2};
  REQUIRE(result.getColumns(singleColName) == MOCK_RESULTS_1_COL);

  vector<string> doubleColName = {MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2};
  REQUIRE(result.getColumns(doubleColName) == MOCK_RESULTS_2_COL);
}

TEST_CASE("SelectClause - evaluate - variable entity") {
  MockPKBReader mockPKB = MockPKBReader(MOCK_STORE);
  mockPKB.mockAllVariables = MOCK_SELECT_CLAUSE_DATA;
  unique_ptr<SynonymArg> mockSynonymArg1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, VARIABLE_ENTITY);
  unique_ptr<SynonymArg> mockSynonymArg2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, VARIABLE_ENTITY);

  SynonymsToSelect mockSynonymsToSelect = {};
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));

  SelectClause selectClause(std::move(mockSynonymsToSelect));
  IntermediateTable result = selectClause.evaluate(mockPKB);

  vector<string> singleColName = {MOCK_SYNONYM_VALUE_2};
  REQUIRE(result.getColumns(singleColName) == MOCK_RESULTS_1_COL);

  vector<string> doubleColName = {MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2};
  REQUIRE(result.getColumns(doubleColName) == MOCK_RESULTS_2_COL);
}

TEST_CASE("SelectClause - evaluate - multi entity") {
  MockPKBReader mockPKB = MockPKBReader(MOCK_STORE);
  mockPKB.mockAllProcedures = MOCK_SELECT_CLAUSE_DATA;
  mockPKB.mockAllVariables = MOCK_SELECT_CLAUSE_DATA_2;
  mockPKB.mockAllConstants = MOCK_SELECT_CLAUSE_DATA_3;
  mockPKB.mockStatements = MOCK_SELECT_CLAUSE_DATA_4;

  unique_ptr<SynonymArg> mockSynonymArg1 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_1, PROCEDURE_ENTITY);
  unique_ptr<SynonymArg> mockSynonymArg2 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_2, VARIABLE_ENTITY);
  unique_ptr<SynonymArg> mockSynonymArg3 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_3, CONSTANT_ENTITY);
  unique_ptr<SynonymArg> mockSynonymArg4 =
      std::make_unique<SynonymArg>(MOCK_SYNONYM_VALUE_4, STMT_ENTITY);

  SynonymsToSelect mockSynonymsToSelect = {};
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg1));
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg2));
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg3));
  mockSynonymsToSelect.push_back(std::move(mockSynonymArg4));

  SelectClause selectClause(std::move(mockSynonymsToSelect));
  IntermediateTable result = selectClause.evaluate(mockPKB);

  vector<string> singleColName = {MOCK_SYNONYM_VALUE_1};
  REQUIRE(result.getColumns(singleColName) == MOCK_RESULTS_1_COL);

  vector<string> doubleColName = {MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2};
  REQUIRE(result.getColumns(doubleColName) == MOCK_RESULTS_2_COL_2);

  vector<string> allColName = {MOCK_SYNONYM_VALUE_1, MOCK_SYNONYM_VALUE_2,
                               MOCK_SYNONYM_VALUE_3, MOCK_SYNONYM_VALUE_4};
  REQUIRE(result.getColumns(allColName) == MOCK_ALL_COL);
}
