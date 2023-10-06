#include <iostream>
#include <catch.hpp>

#include "IntermediateTableTestData.h"
#include "IntermediateTableTestUtils.h"
#include "qps/intermediateTable/IntermediateTableUtils.h"

IntermediateTable DOUBLE_COLUMN_TABLE_FROM_PAIR_1 =
    IntermediateTable(COL_NAME_1, COL_NAME_2, PAIR_DATA);

IntermediateTable DOUBLE_COLUMN_TABLE_FROM_VECTORS_1 =
    IntermediateTable(DOUBLE_COL_NAME_VECTOR, DOUBLE_COL_VECTOR_DATA);

IntermediateTable DOUBLE_COLUMN_TABLE_FROM_VECTORS_2 =
    IntermediateTable(doubleColNameVector2, DOUBLE_COL_VECTOR_DATA_2);

IntermediateTable MULTI_COLUMN_TABLE_1 =
    IntermediateTable(MULTI_COL_NAME_VECTOR_1, MULTI_COL_DATA_1);

IntermediateTable MULTI_COLUMN_TABLE_2 =
    IntermediateTable(MULTI_COL_NAME_VECTOR_2, MULTI_COL_DATA_2);

IntermediateTable WILDCARD_TABLE = IntermediateTable::makeWildcardTable();

IntermediateTable EMPTY_TABLE = IntermediateTable::makeEmptyTable();

TEST_CASE("IntermediateTable - constructors + getData") {
  REQUIRE(isVectorsSameAsPairs(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.getData(),
                               PAIR_DATA));
  REQUIRE(isVectorsSameAsPairs(DOUBLE_COLUMN_TABLE_FROM_VECTORS_1.getData(),
                               PAIR_DATA));
  std::cout << "expect \"row 0 incorrect\":" << std::endl;
  REQUIRE(isVectorsSameAsPairs(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2.getData(),
                               PAIR_DATA) == false);

  REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.getData() ==
          DOUBLE_COLUMN_TABLE_FROM_VECTORS_1.getData());
  REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.getData() == DOUBLE_COL_VECTOR_DATA);
  REQUIRE(DOUBLE_COLUMN_TABLE_FROM_VECTORS_1.getData() ==
          DOUBLE_COL_VECTOR_DATA);
  REQUIRE(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2.getData() ==
          DOUBLE_COL_VECTOR_DATA_2);
}

TEST_CASE("IntermediateTable - makeEmptyTable") {
  REQUIRE(EMPTY_TABLE.isTableEmpty());
  REQUIRE(EMPTY_TABLE.isTableEmptyAndNotWildcard());
  REQUIRE(EMPTY_TABLE.isTableWildcard() == false);
  REQUIRE(EMPTY_TABLE.getData().empty());
}

TEST_CASE("IntermediateTable - makeWildcardTable") {
  REQUIRE(WILDCARD_TABLE.isTableWildcard());
  REQUIRE(WILDCARD_TABLE.isTableEmpty());
  REQUIRE(WILDCARD_TABLE.isTableEmptyAndNotWildcard() == false);
  REQUIRE(WILDCARD_TABLE.getData().empty());
}

TEST_CASE("IntermediateTable - getColumns") {
  // get 0 column
  vector<string> vectorWithNoCol = {};
  set<string> expectedNoCol = {};
  REQUIRE(MULTI_COLUMN_TABLE_1.getColumns(vectorWithNoCol) == expectedNoCol);

  // get 1 column
  vector<string> vectorWithOneCol = {COL_NAME_4};
  set<string> expectedOneCol = {"0", "2", "4", "6", "6", "4", "2"};
  REQUIRE(MULTI_COLUMN_TABLE_1.getColumns(vectorWithOneCol) == expectedOneCol);

  // get >1 columns
  vector<string> vectorWithMultiCols = {COL_NAME_1, COL_NAME_3, COL_NAME_4};
  set<string> expectedMultiCols = {"cat 1 0",  "pineapple 3 2", "dog 5 4",
                                   "woof 7 6", "durian 5 6",    "cucumber 3 4",
                                   "mouse 1 2"};
  REQUIRE(MULTI_COLUMN_TABLE_1.getColumns(vectorWithMultiCols) ==
          expectedMultiCols);

  // get non-existent columns
  vector<string> vectorWithNonExistentCols = {COL_NAME_1, COL_NAME_3,
                                              COL_NAME_6};
  set<string> expectedWithNonExistent = {};
  REQUIRE(MULTI_COLUMN_TABLE_1.getColumns(vectorWithNonExistentCols) ==
          expectedWithNonExistent);
}

TEST_CASE("IntermediateTable - isColExists") {
  REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.isColExists(COL_NAME_1));
  REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.isColExists(COL_NAME_2));
  REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.isColExists(COL_NAME_3) == false);
  REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.isColExists(COL_NAME_4) == false);
  REQUIRE(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2.isColExists(COL_NAME_3));
  REQUIRE(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2.isColExists(COL_NAME_4));

  auto newTable = DOUBLE_COLUMN_TABLE_FROM_VECTORS_1.join(
      DOUBLE_COLUMN_TABLE_FROM_VECTORS_2);
}

TEST_CASE("IntermediateTable - getSharedColNames, getSharedColIndexes") {
  REQUIRE(getSharedColNames(DOUBLE_COLUMN_TABLE_FROM_PAIR_1,
                            MULTI_COLUMN_TABLE_1) == DOUBLE_COL_NAME_VECTOR);
  vector<int> sharedColIndex1 = {0, 1};
  vector<int> sharedColIndex2 = {3, 2};
  REQUIRE(getSharedColIndexes(DOUBLE_COLUMN_TABLE_FROM_PAIR_1,
                              MULTI_COLUMN_TABLE_1) ==
          pair(sharedColIndex1, sharedColIndex2));
}

TEST_CASE("IntermediateTable - join - cross") {
  IntermediateTable crossTable = DOUBLE_COLUMN_TABLE_FROM_VECTORS_1.join(
      DOUBLE_COLUMN_TABLE_FROM_VECTORS_2);
  REQUIRE(crossTable.getData() == DOUBLE_COL_VECTOR_DATA_CROSS);
}

TEST_CASE("IntermediateTable - join - inner join") {
  IntermediateTable joinTable = MULTI_COLUMN_TABLE_1.join(MULTI_COLUMN_TABLE_2);
  REQUIRE(joinTable.getData() == MULTI_COL_DATA_JOIN);
}

TEST_CASE("IntermediateTable - join - any_x_empty") {
  // data x EMPTY
  IntermediateTable dataJoinEmptyTable = MULTI_COLUMN_TABLE_1.join(EMPTY_TABLE);
  REQUIRE(dataJoinEmptyTable.isTableEmpty());
  REQUIRE(dataJoinEmptyTable.getData().empty());

  // EMPTY x data
  IntermediateTable emptyJoinDataTable = EMPTY_TABLE.join(MULTI_COLUMN_TABLE_1);
  REQUIRE(emptyJoinDataTable.isTableEmpty());
  REQUIRE(emptyJoinDataTable.getData().empty());

  // WILDCARD X EMPTY
  IntermediateTable wildcardJoinEmptyTable = WILDCARD_TABLE.join(EMPTY_TABLE);
  REQUIRE(wildcardJoinEmptyTable.isTableEmpty());
  REQUIRE(wildcardJoinEmptyTable.getData().empty());

  // EMPTY X WILDCARD
  IntermediateTable emptyJoinWildcardTable = EMPTY_TABLE.join(WILDCARD_TABLE);
  REQUIRE(emptyJoinWildcardTable.isTableEmpty());
  REQUIRE(emptyJoinWildcardTable.getData().empty());

  // EMPTY X EMPTY
  IntermediateTable emptyJoinEmptyTable = EMPTY_TABLE.join(EMPTY_TABLE);
  REQUIRE(emptyJoinEmptyTable.isTableEmpty());
  REQUIRE(emptyJoinEmptyTable.getData().empty());
}

TEST_CASE("IntermediateTable - join - any_x_wildcard") {
  // DATA X WILDCARD
  IntermediateTable dataJoinWildcardTable =
      MULTI_COLUMN_TABLE_1.join(WILDCARD_TABLE);
  REQUIRE(dataJoinWildcardTable.isTableWildcard() == false);
  REQUIRE(dataJoinWildcardTable.getData() == MULTI_COL_DATA_1);

  // WILDCARD X DATA
  IntermediateTable wildcardJoinDataTable =
      WILDCARD_TABLE.join(MULTI_COLUMN_TABLE_1);
  REQUIRE(wildcardJoinDataTable.isTableWildcard() == false);
  REQUIRE(wildcardJoinDataTable.getData() == MULTI_COL_DATA_1);

  // WILDCARD X WILDCARD
  IntermediateTable wildcardJoinWildcardTable =
      WILDCARD_TABLE.join(WILDCARD_TABLE);
  REQUIRE(wildcardJoinWildcardTable.isTableWildcard() == true);
  REQUIRE(wildcardJoinWildcardTable.getData().empty());

  // WILDCARD X EMPTY and vice versa is already
  // tested in "any_x_empty" tests
}
