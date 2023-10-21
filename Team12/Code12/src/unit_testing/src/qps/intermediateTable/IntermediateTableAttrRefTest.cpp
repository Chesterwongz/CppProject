#include <catch.hpp>

#include "IntermediateTableTestUtils.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "qps/intermediateTable/IntermediateTableUtils.h"
#include "testData/SynonymResTestData.h"

IntermediateTable DOUBLE_COLUMN_SYNONYM_RES_TABLE_1 =
    IntermediateTableFactory::buildIntermediateTable(
        SYNONYM_RES_COL_NAME_1, DOUBLE_COL_SYNONYM_RES_DATA);

IntermediateTable DOUBLE_COLUMN_SYNONYM_RES_TABLE_2 =
    IntermediateTableFactory::buildIntermediateTable(
        SYNONYM_RES_COL_NAME_2, DOUBLE_COL_SYNONYM_RES_DATA_2);

IntermediateTable DOUBLE_COLUMN_SYNONYM_RES_TABLE_3 =
    IntermediateTableFactory::buildIntermediateTable(
        SYNONYM_RES_COL_NAME_3, DOUBLE_COL_SYNONYM_RES_DATA_3);

IntermediateTable MULTI_COLUMN_SYNONYM_RES_TABLE_1 =
    IntermediateTableFactory::buildIntermediateTable(
        SYNONYM_RES_MULTI_COL_NAME_1, MULTI_COL_SYNONYM_RES_DATA_1);

IntermediateTable MULTI_COLUMN_SYNONYM_RES_TABLE_2 =
    IntermediateTableFactory::buildIntermediateTable(
        SYNONYM_RES_MULTI_COL_NAME_2, MULTI_COL_SYNONYM_RES_DATA_2);

TEST_CASE("IntermediateTable - constructors + getTableData") {
  REQUIRE(DOUBLE_COLUMN_SYNONYM_RES_TABLE_1.getTableData() ==
          DOUBLE_COL_SYNONYM_RES_DATA);
  REQUIRE(DOUBLE_COLUMN_SYNONYM_RES_TABLE_2.getTableData() ==
          DOUBLE_COL_SYNONYM_RES_DATA_2);
  REQUIRE(DOUBLE_COLUMN_SYNONYM_RES_TABLE_1.getTableData() ==
          DOUBLE_COL_SYNONYM_RES_DATA);
  REQUIRE(DOUBLE_COLUMN_SYNONYM_RES_TABLE_2.getTableData() ==
          DOUBLE_COL_SYNONYM_RES_DATA_2);
}

TEST_CASE("IntermediateTable - getColumns - SynonymRes") {
  // get 0 column
  vector<pair<string, AttrRefEnum>> vectorWithNoCol = {};
  unordered_set<string> expectedNoCol = {};
  REQUIRE(MULTI_COLUMN_SYNONYM_RES_TABLE_1.getColumns(vectorWithNoCol) ==
          expectedNoCol);

  // get 1 column
  vector<pair<string, AttrRefEnum>> vectorWithOneCol = {
      {"calls", AttrRefEnum::PROC_NAME_ENUM}};
  unordered_set<string> expectedOneCol = {SYNONYM_VAL_1B, SYNONYM_VAL_2B};
  REQUIRE(MULTI_COLUMN_SYNONYM_RES_TABLE_1.getColumns(vectorWithOneCol) ==
          expectedOneCol);

  // get >1 columns
  vector<pair<string, AttrRefEnum>> vectorWithMultiCols = {
      {"calls", AttrRefEnum::PROC_NAME_ENUM},
      {"stmt", AttrRefEnum::STMT_NUM_ENUM},
      {"constant", AttrRefEnum::VALUE_ENUM}};
  unordered_set<string> expectedMultiCols = {
      SYNONYM_VAL_1B + " " + SYNONYM_VAL_1 + " " + SYNONYM_VAL_1,
      SYNONYM_VAL_1B + " " + SYNONYM_VAL_2 + " " + SYNONYM_VAL_2,
      SYNONYM_VAL_2B + " " + SYNONYM_VAL_3 + " " + SYNONYM_VAL_3,
      SYNONYM_VAL_2B + " " + SYNONYM_VAL_4 + " " + SYNONYM_VAL_4,
  };
  REQUIRE(MULTI_COLUMN_SYNONYM_RES_TABLE_1.getColumns(vectorWithMultiCols) ==
          expectedMultiCols);

  // get non-existent column names
  unordered_set<string> expectedWithNonExistent = {};
  REQUIRE(MULTI_COLUMN_SYNONYM_RES_TABLE_2.getColumns(vectorWithMultiCols) ==
          expectedWithNonExistent);

  // non-existent attrRefs will be caught by parser
}

TEST_CASE("IntermediateTable - isColExists - SynonymRes") {
  REQUIRE(MULTI_COLUMN_SYNONYM_RES_TABLE_2.isColExists("var"));
  REQUIRE(MULTI_COLUMN_SYNONYM_RES_TABLE_2.isColExists("proc"));
}

TEST_CASE(
    "IntermediateTable - getSharedColNames, getSharedColIndexes - SynonymRes") {
  REQUIRE(IntermediateTableUtils::getSharedColNames(
              DOUBLE_COLUMN_SYNONYM_RES_TABLE_2,
              MULTI_COLUMN_SYNONYM_RES_TABLE_2) == SYNONYM_RES_COL_NAME_2);
  vector<int> sharedColIndex1 = {0, 1};
  vector<int> sharedColIndex2 = {0, 3};
  REQUIRE(IntermediateTableUtils::getSharedColIndexes(
              DOUBLE_COLUMN_SYNONYM_RES_TABLE_2,
              MULTI_COLUMN_SYNONYM_RES_TABLE_2) ==
          pair(sharedColIndex1, sharedColIndex2));
}

TEST_CASE("IntermediateTable - join_cross - SynonymRes") {
  IntermediateTable crossTable =
      DOUBLE_COLUMN_SYNONYM_RES_TABLE_1.join(DOUBLE_COLUMN_SYNONYM_RES_TABLE_2);
  vector<vector<SynonymRes>> expected = DOUBLE_COL_SYNONYM_RES_DATA_CROSS;
  vector<vector<SynonymRes>> actual = crossTable.getTableData();

  REQUIRE(expected.size() == actual.size());
  for (const auto &row : expected) {
    REQUIRE(std::count(actual.begin(), actual.end(), row) == 1);
  }
}

TEST_CASE("IntermediateTable - join_inner_join - SynonymRes") {
  IntermediateTable joinTable =
      MULTI_COLUMN_SYNONYM_RES_TABLE_1.join(MULTI_COLUMN_SYNONYM_RES_TABLE_2);
  REQUIRE(joinTable.getTableData() == MULTI_COL_SYNONYM_RES_DATA_INNER_JOIN);
}

TEST_CASE("IntermediateTable - join_inner_join_on - SynonymRes") {
  IntermediateTable joinTable = DOUBLE_COLUMN_SYNONYM_RES_TABLE_1.join(
      DOUBLE_COLUMN_SYNONYM_RES_TABLE_3, {"calls", ATTR_REF_PROC_NAME},
      {"print", ATTR_REF_VAR_NAME});
  joinTable.printTable();
  vector<vector<SynonymRes>> expected = {
      {MOCK_CONSTANT_SYN_1, MOCK_PRINT_SYN_1, MOCK_CONSTANT_SYN_2,
       MOCK_PRINT_SYN_2},
      {MOCK_CONSTANT_SYN_2, MOCK_PRINT_SYN_2, MOCK_CONSTANT_SYN_2,
       MOCK_PRINT_SYN_2},
  };
  REQUIRE(joinTable.getTableData() == expected);
}

TEST_CASE("IntermediateTable - join - any_x_empty - SynonymRes") {
  // data x EMPTY
  IntermediateTable dataJoinEmptyTable =
      MULTI_COLUMN_SYNONYM_RES_TABLE_1.join(EMPTY_TABLE);
  REQUIRE(dataJoinEmptyTable.isTableEmptyAndNotWildcard());
  REQUIRE(dataJoinEmptyTable.getColNames().empty());

  // EMPTY x data
  IntermediateTable emptyJoinDataTable =
      EMPTY_TABLE.join(MULTI_COLUMN_SYNONYM_RES_TABLE_1);
  REQUIRE(emptyJoinDataTable.isTableEmptyAndNotWildcard());
  REQUIRE(emptyJoinDataTable.getColNames().empty());

  // WILDCARD X EMPTY
  IntermediateTable wildcardJoinEmptyTable = WILDCARD_TABLE.join(EMPTY_TABLE);
  REQUIRE(wildcardJoinEmptyTable.isTableEmptyAndNotWildcard());
  REQUIRE(wildcardJoinEmptyTable.getColNames().empty());

  // EMPTY X WILDCARD
  IntermediateTable emptyJoinWildcardTable = EMPTY_TABLE.join(WILDCARD_TABLE);
  REQUIRE(emptyJoinWildcardTable.isTableEmpty());
  REQUIRE(emptyJoinWildcardTable.getColNames().empty());

  // EMPTY X EMPTY
  IntermediateTable emptyJoinEmptyTable = EMPTY_TABLE.join(EMPTY_TABLE);
  REQUIRE(emptyJoinEmptyTable.isTableEmptyAndNotWildcard());
  REQUIRE(emptyJoinEmptyTable.getColNames().empty());
}

TEST_CASE("IntermediateTable - join - any_x_wildcard - SynonymRes") {
  // DATA X WILDCARD
  IntermediateTable dataJoinWildcardTable =
      MULTI_COLUMN_SYNONYM_RES_TABLE_1.join(WILDCARD_TABLE);
  REQUIRE(dataJoinWildcardTable.isTableWildcard() == false);
  REQUIRE(dataJoinWildcardTable.getTableData() == MULTI_COL_SYNONYM_RES_DATA_1);

  // WILDCARD X DATA
  IntermediateTable wildcardJoinDataTable =
      WILDCARD_TABLE.join(MULTI_COLUMN_SYNONYM_RES_TABLE_1);
  REQUIRE(wildcardJoinDataTable.isTableWildcard() == false);
  REQUIRE(wildcardJoinDataTable.getTableData() == MULTI_COL_SYNONYM_RES_DATA_1);

  // WILDCARD X WILDCARD
  IntermediateTable wildcardJoinWildcardTable =
      WILDCARD_TABLE.join(WILDCARD_TABLE);
  REQUIRE(wildcardJoinWildcardTable.isTableWildcard() == true);

  // WILDCARD X EMPTY and vice versa is already
  // tested in "any_x_empty" tests
}
