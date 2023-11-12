#include <catch.hpp>

#include "IntermediateTableTestUtils.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "qps/intermediateTable/IntermediateTableUtils.h"
#include "testData/StringTestData.h"

TEST_CASE("IntermediateTable - constructors + getDataAsStrings") {
  IntermediateTable doubleColumnTableFromPair1 =
      IntermediateTableFactory::buildIntermediateTable(COL_NAME_1, COL_NAME_2,
                                                       PAIR_DATA);
  IntermediateTable doubleColumnTableFromVectors1 =
      IntermediateTableFactory::buildIntermediateTable(
          DOUBLE_COL_NAME_VECTOR,
          convertToSynonymResCol(DOUBLE_COL_VECTOR_DATA));
  IntermediateTable doubleColumnTableFromVectors2 =
      IntermediateTableFactory::buildIntermediateTable(
          doubleColNameVector2,
          convertToSynonymResCol(DOUBLE_COL_VECTOR_DATA_2));

  REQUIRE(isVectorsSameAsPairs(doubleColumnTableFromPair1.getDataAsStrings(),
                               PAIR_DATA));
  REQUIRE(isVectorsSameAsPairs(doubleColumnTableFromVectors1.getDataAsStrings(),
                               PAIR_DATA));
  REQUIRE(isVectorsSameAsPairs(doubleColumnTableFromVectors2.getDataAsStrings(),
                               PAIR_DATA) == false);

  REQUIRE(doubleColumnTableFromPair1.getDataAsStrings() ==
          doubleColumnTableFromVectors1.getDataAsStrings());
  REQUIRE(doubleColumnTableFromPair1.getDataAsStrings() ==
          DOUBLE_COL_VECTOR_DATA);
  REQUIRE(doubleColumnTableFromVectors1.getDataAsStrings() ==
          DOUBLE_COL_VECTOR_DATA);
  REQUIRE(doubleColumnTableFromVectors2.getDataAsStrings() ==
          DOUBLE_COL_VECTOR_DATA_2);
}

TEST_CASE("IntermediateTable - makeEmptyTable") {
  REQUIRE(EMPTY_TABLE.isTableEmpty());
  REQUIRE(EMPTY_TABLE.isTableEmptyAndNotWildcard());
  REQUIRE(EMPTY_TABLE.isTableWildcard() == false);
  REQUIRE(EMPTY_TABLE.getDataAsStrings().empty());
}

TEST_CASE("IntermediateTable - makeWildcardTable") {
  REQUIRE(WILDCARD_TABLE.isTableWildcard());
  REQUIRE(WILDCARD_TABLE.isTableEmpty());
  REQUIRE(WILDCARD_TABLE.isTableEmptyAndNotWildcard() == false);
  REQUIRE(WILDCARD_TABLE.getDataAsStrings().empty());
}

TEST_CASE("IntermediateTable - getColumns") {
  IntermediateTable multiColumnTable1 =
      IntermediateTableFactory::buildIntermediateTable(
          MULTI_COL_NAME_VECTOR_1, convertToSynonymResCol(MULTI_COL_DATA_1));

  // get 0 column
  vector<string> vectorWithNoCol = {};
  unordered_set<string> expectedNoCol = {};
  REQUIRE(multiColumnTable1.getColumns(vectorWithNoCol) == expectedNoCol);

  // get 1 column
  vector<string> vectorWithOneCol = {COL_NAME_4};
  unordered_set<string> expectedOneCol = {"0", "2", "4", "6", "6", "4", "2"};
  REQUIRE(multiColumnTable1.getColumns(vectorWithOneCol) == expectedOneCol);

  // get >1 columns
  vector<string> vectorWithMultiCols = {COL_NAME_1, COL_NAME_3, COL_NAME_4};
  unordered_set<string> expectedMultiCols = {
      "cat 1 0",    "pineapple 3 2", "dog 5 4",  "woof 7 6",
      "durian 5 6", "cucumber 3 4",  "mouse 1 2"};
  REQUIRE(multiColumnTable1.getColumns(vectorWithMultiCols) ==
          expectedMultiCols);

  // get non-existent columns
  vector<string> vectorWithNonExistentCols = {COL_NAME_1, COL_NAME_3,
                                              COL_NAME_6};
  unordered_set<string> expectedWithNonExistent = {};
  REQUIRE(multiColumnTable1.getColumns(vectorWithNonExistentCols) ==
          expectedWithNonExistent);
}

TEST_CASE("IntermediateTable - isColExists") {
  IntermediateTable doubleColumnTableFromPair1 =
      IntermediateTableFactory::buildIntermediateTable(COL_NAME_1, COL_NAME_2,
                                                       PAIR_DATA);
  IntermediateTable doubleColumnTableFromVectors2 =
      IntermediateTableFactory::buildIntermediateTable(
          doubleColNameVector2,
          convertToSynonymResCol(DOUBLE_COL_VECTOR_DATA_2));

  REQUIRE(doubleColumnTableFromPair1.isColExists(COL_NAME_1));
  REQUIRE(doubleColumnTableFromPair1.isColExists(COL_NAME_2));
  REQUIRE(doubleColumnTableFromPair1.isColExists(COL_NAME_3) == false);
  REQUIRE(doubleColumnTableFromPair1.isColExists(COL_NAME_4) == false);
  REQUIRE(doubleColumnTableFromVectors2.isColExists(COL_NAME_3));
  REQUIRE(doubleColumnTableFromVectors2.isColExists(COL_NAME_4));
}

TEST_CASE("IntermediateTable - getSharedColNames, getSharedColIndexes") {
  IntermediateTable multiColumnTable1 =
      IntermediateTableFactory::buildIntermediateTable(
          MULTI_COL_NAME_VECTOR_1, convertToSynonymResCol(MULTI_COL_DATA_1));

  IntermediateTable doubleColumnTableFromPair1 =
      IntermediateTableFactory::buildIntermediateTable(COL_NAME_1, COL_NAME_2,
                                                       PAIR_DATA);
  IntermediateTable doubleColumnTableFromVectors1 =
      IntermediateTableFactory::buildIntermediateTable(
          DOUBLE_COL_NAME_VECTOR,
          convertToSynonymResCol(DOUBLE_COL_VECTOR_DATA));
  IntermediateTable doubleColumnTableFromVectors2 =
      IntermediateTableFactory::buildIntermediateTable(
          doubleColNameVector2,
          convertToSynonymResCol(DOUBLE_COL_VECTOR_DATA_2));

  REQUIRE(IntermediateTableUtils::getSharedColNames(doubleColumnTableFromPair1,
                                                    multiColumnTable1) ==
          DOUBLE_COL_NAME_VECTOR);
  vector<int> sharedColIndex1 = {0, 1};
  vector<int> sharedColIndex2 = {3, 2};
  REQUIRE(IntermediateTableUtils::getSharedColIndexes(
              doubleColumnTableFromPair1, multiColumnTable1) ==
          pair(sharedColIndex1, sharedColIndex2));
}

TEST_CASE("IntermediateTable - join - cross") {
  IntermediateTable doubleColumnTableFromVectors1 =
      IntermediateTableFactory::buildIntermediateTable(
          DOUBLE_COL_NAME_VECTOR,
          convertToSynonymResCol(DOUBLE_COL_VECTOR_DATA));
  IntermediateTable doubleColumnTableFromVectors2 =
      IntermediateTableFactory::buildIntermediateTable(
          doubleColNameVector2,
          convertToSynonymResCol(DOUBLE_COL_VECTOR_DATA_2));

  IntermediateTable crossTable =
      doubleColumnTableFromVectors1.join(doubleColumnTableFromVectors2);
  REQUIRE(crossTable.getDataAsStrings() == DOUBLE_COL_VECTOR_DATA_CROSS);
}

TEST_CASE("IntermediateTable - join - inner join") {
  IntermediateTable table1 = IntermediateTableFactory::buildIntermediateTable(
      MULTI_COL_NAME_VECTOR_1, convertToSynonymResCol(MULTI_COL_DATA_1));

  IntermediateTable table2 = IntermediateTableFactory::buildIntermediateTable(
      MULTI_COL_NAME_VECTOR_2, convertToSynonymResCol(MULTI_COL_DATA_2));

  IntermediateTable joinTable = table1.join(table2);
  REQUIRE(joinTable.getDataAsStrings() == MULTI_COL_DATA_JOIN);
}

TEST_CASE("IntermediateTable - join - empty_x_empty") {
  IntermediateTable empty1 =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  IntermediateTable empty2 =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  IntermediateTable emptyJoinEmptyTable = empty1.join(empty2);
  REQUIRE(emptyJoinEmptyTable.isTableEmptyAndNotWildcard());
  REQUIRE(emptyJoinEmptyTable.getColNames().empty());
}

TEST_CASE("IntermediateTable - join - data_x_empty") {
  IntermediateTable table1 = IntermediateTableFactory::buildIntermediateTable(
      MULTI_COL_NAME_VECTOR_1, convertToSynonymResCol(MULTI_COL_DATA_1));
  IntermediateTable empty =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  IntermediateTable dataJoinEmptyTable = table1.join(empty);
  REQUIRE(dataJoinEmptyTable.isTableEmptyAndNotWildcard());
  REQUIRE(dataJoinEmptyTable.getColNames().empty());
}

TEST_CASE("IntermediateTable - join - empty_x_data") {
  IntermediateTable table1 = IntermediateTableFactory::buildIntermediateTable(
      MULTI_COL_NAME_VECTOR_1, convertToSynonymResCol(MULTI_COL_DATA_1));
  IntermediateTable empty =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  IntermediateTable emptyJoinDataTable = empty.join(table1);
  REQUIRE(emptyJoinDataTable.isTableEmptyAndNotWildcard());
  REQUIRE(emptyJoinDataTable.getColNames().empty());
}

TEST_CASE("IntermediateTable - join - wildcard_x_empty") {
  IntermediateTable wildcard =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  IntermediateTable empty =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  IntermediateTable wildcardJoinEmptyTable = wildcard.join(empty);
  REQUIRE(wildcardJoinEmptyTable.isTableEmptyAndNotWildcard());
  REQUIRE(wildcardJoinEmptyTable.getColNames().empty());
}

TEST_CASE("IntermediateTable - join - empty_x_wildcard") {
  IntermediateTable wildcard =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  IntermediateTable empty =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  IntermediateTable emptyJoinWildcardTable = empty.join(wildcard);
  REQUIRE(emptyJoinWildcardTable.isTableEmptyAndNotWildcard());
  REQUIRE(emptyJoinWildcardTable.getColNames().empty());
}

TEST_CASE("IntermediateTable - join - data_x_wildcard") {
  IntermediateTable table1 = IntermediateTableFactory::buildIntermediateTable(
      MULTI_COL_NAME_VECTOR_1, convertToSynonymResCol(MULTI_COL_DATA_1));

  IntermediateTable wildcard1 =
      IntermediateTableFactory::buildWildcardIntermediateTable();

  IntermediateTable dataJoinWildcardTable = table1.join(wildcard1);
  REQUIRE(dataJoinWildcardTable.isTableWildcard() == false);
  REQUIRE(dataJoinWildcardTable.getDataAsStrings() == MULTI_COL_DATA_1);
}

TEST_CASE("IntermediateTable - join - wildcard_x_data") {
  IntermediateTable table1 = IntermediateTableFactory::buildIntermediateTable(
      MULTI_COL_NAME_VECTOR_1, convertToSynonymResCol(MULTI_COL_DATA_1));

  IntermediateTable wildcard1 =
      IntermediateTableFactory::buildWildcardIntermediateTable();

  IntermediateTable wildcardJoinDataTable = wildcard1.join(table1);
  REQUIRE(wildcardJoinDataTable.isTableWildcard() == false);
  REQUIRE(wildcardJoinDataTable.getDataAsStrings() == MULTI_COL_DATA_1);
}

TEST_CASE("IntermediateTable - join - wildcard_x_wildcard") {
  IntermediateTable wildcard1 =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  IntermediateTable wildcard2 =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  IntermediateTable wildcardJoinWildcardTable = wildcard1.join(wildcard2);
  REQUIRE(wildcardJoinWildcardTable.isTableWildcard() == true);
  REQUIRE(wildcardJoinWildcardTable.getDataAsStrings().empty());
}

// WILDCARD X EMPTY and vice versa is already
// tested in "any_x_empty" tests

TEST_CASE("IntermediateTable - getDifference : ANY - WILDCARD") {
  TableDataType randomData = {{SynonymResFactory::buildDefaultSynonym("1"),
                               SynonymResFactory::buildDefaultSynonym("2")},
                              {SynonymResFactory::buildDefaultSynonym("3"),
                               SynonymResFactory::buildDefaultSynonym("4")}};
  vector<string> colNames = {"a", "b"};
  IntermediateTable randomTable =
      IntermediateTableFactory::buildIntermediateTable(colNames, randomData);

  IntermediateTable wildcardTable =
      IntermediateTableFactory::buildWildcardIntermediateTable();

  IntermediateTable resultTable = randomTable.getDifference(wildcardTable);

  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("IntermediateTable - getDifference : ANY - EMPTY") {
  TableDataType randomData = {{SynonymResFactory::buildDefaultSynonym("1"),
                               SynonymResFactory::buildDefaultSynonym("2")},
                              {SynonymResFactory::buildDefaultSynonym("3"),
                               SynonymResFactory::buildDefaultSynonym("4")}};
  vector<string> colNames = {"a", "b"};
  IntermediateTable randomTable =
      IntermediateTableFactory::buildIntermediateTable(colNames, randomData);

  IntermediateTable emptyTable =
      IntermediateTableFactory::buildEmptyIntermediateTable();

  IntermediateTable resultTable = randomTable.getDifference(emptyTable);

  REQUIRE(isTableDataSame(resultTable.getTableData(), randomData));
}

TEST_CASE("IntermediateTable - getDifference : EMPTY - ANY") {
  TableDataType randomData = {{SynonymResFactory::buildDefaultSynonym("1"),
                               SynonymResFactory::buildDefaultSynonym("2")},
                              {SynonymResFactory::buildDefaultSynonym("3"),
                               SynonymResFactory::buildDefaultSynonym("4")}};
  vector<string> colNames = {"a", "b"};
  IntermediateTable randomTable =
      IntermediateTableFactory::buildIntermediateTable(colNames, randomData);

  IntermediateTable emptyTable =
      IntermediateTableFactory::buildEmptyIntermediateTable();

  IntermediateTable resultTable = emptyTable.getDifference(randomTable);

  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("IntermediateTable - getDifference : WILDCARD - ANY") {
  TableDataType randomData = {{SynonymResFactory::buildDefaultSynonym("1"),
                               SynonymResFactory::buildDefaultSynonym("2")},
                              {SynonymResFactory::buildDefaultSynonym("3"),
                               SynonymResFactory::buildDefaultSynonym("4")}};
  vector<string> colNames = {"a", "b"};
  IntermediateTable randomTable =
      IntermediateTableFactory::buildIntermediateTable(colNames, randomData);

  IntermediateTable wildcardTable =
      IntermediateTableFactory::buildWildcardIntermediateTable();

  IntermediateTable resultTable = wildcardTable.getDifference(randomTable);

  REQUIRE(resultTable.isTableEmpty());
}

TEST_CASE("IntermediateTable - getDifference : ANY - ANY") {
  vector<string> colNames = {"a", "b"};

  TableDataType randomData1 = {{SynonymResFactory::buildDefaultSynonym("1"),
                                SynonymResFactory::buildDefaultSynonym("2")},
                               {SynonymResFactory::buildDefaultSynonym("3"),
                                SynonymResFactory::buildDefaultSynonym("4")}};

  IntermediateTable randomTable1 =
      IntermediateTableFactory::buildIntermediateTable(colNames, randomData1);

  TableDataType randomData2 = {{SynonymResFactory::buildDefaultSynonym("5"),
                                SynonymResFactory::buildDefaultSynonym("2")},
                               {SynonymResFactory::buildDefaultSynonym("3"),
                                SynonymResFactory::buildDefaultSynonym("4")}};

  IntermediateTable randomTable2 =
      IntermediateTableFactory::buildIntermediateTable(colNames, randomData2);

  IntermediateTable resultTable = randomTable1.getDifference(randomTable2);

  TableDataType expectedData = {{SynonymResFactory::buildDefaultSynonym("1"),
                                 SynonymResFactory::buildDefaultSynonym("2")}};

  REQUIRE(isTableDataSame(resultTable.getTableData(), expectedData));
}
