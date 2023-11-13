#include <catch.hpp>

#include "IntermediateTableTestUtils.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "qps/intermediateTable/IntermediateTableUtils.h"
#include "testData/SynonymResTestData.h"

TEST_CASE("IntermediateTable - constructors + getTableData") {
  IntermediateTable doubleColumnSynResTable1 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_1, DOUBLE_COL_SYNONYM_RES_DATA);
  IntermediateTable doubleColumnSynResTable2 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_2, DOUBLE_COL_SYNONYM_RES_DATA_2);

  REQUIRE(isTableDataSame(doubleColumnSynResTable1.getTableData(),
                          DOUBLE_COL_SYNONYM_RES_DATA));
  REQUIRE(isTableDataSame(doubleColumnSynResTable2.getTableData(),
                          DOUBLE_COL_SYNONYM_RES_DATA_2));
  REQUIRE(isTableDataSame(doubleColumnSynResTable1.getTableData(),
                          DOUBLE_COL_SYNONYM_RES_DATA));
  REQUIRE(isTableDataSame(doubleColumnSynResTable2.getTableData(),
                          DOUBLE_COL_SYNONYM_RES_DATA_2));
}

TEST_CASE("IntermediateTable - getColumns - SynonymRes") {
  IntermediateTable multiColSynResTable1 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_MULTI_COL_NAME_1, MULTI_COL_SYNONYM_RES_DATA_1);
  IntermediateTable multiColSynResTable2 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_MULTI_COL_NAME_2, MULTI_COL_SYNONYM_RES_DATA_2);

  // get 0 column
  vector<unique_ptr<SynonymArg>> vectorWithNoCol = {};
  unordered_set<string> expectedNoCol = {};
  REQUIRE(multiColSynResTable1.getColumns(vectorWithNoCol) == expectedNoCol);

  // get 1 column
  vector<unique_ptr<SynonymArg>> vectorWithOneCol {};
  vectorWithOneCol.push_back(
      std::make_unique<SynonymArg>("calls", CALL_ENTITY, ATTR_REF_PROC_NAME));
  unordered_set<string> expectedOneCol = {SYNONYM_VAL_1B, SYNONYM_VAL_2B};
  REQUIRE(multiColSynResTable1.getColumns(vectorWithOneCol) == expectedOneCol);

  // get >1 columns
  vector<unique_ptr<SynonymArg>> vectorWithMultiCols {};
  vectorWithMultiCols.push_back(
      std::make_unique<SynonymArg>("calls", CALL_ENTITY, ATTR_REF_PROC_NAME));
  vectorWithMultiCols.push_back(
      std::make_unique<SynonymArg>("stmt", STMT_ENTITY, ATTR_REF_STMT_NUMBER));
  vectorWithMultiCols.push_back(std::make_unique<SynonymArg>(
      "constant", CONSTANT_ENTITY, ATTR_REF_VALUE));
  unordered_set<string> expectedMultiCols = {
      SYNONYM_VAL_1B + " " + SYNONYM_VAL_1 + " " + SYNONYM_VAL_1,
      SYNONYM_VAL_1B + " " + SYNONYM_VAL_2 + " " + SYNONYM_VAL_2,
      SYNONYM_VAL_2B + " " + SYNONYM_VAL_3 + " " + SYNONYM_VAL_3,
      SYNONYM_VAL_2B + " " + SYNONYM_VAL_4 + " " + SYNONYM_VAL_4,
  };
  REQUIRE(multiColSynResTable1.getColumns(vectorWithMultiCols) ==
          expectedMultiCols);

  // get non-existent column names
  unordered_set<string> expectedWithNonExistent = {};
  REQUIRE(multiColSynResTable2.getColumns(vectorWithMultiCols) ==
          expectedWithNonExistent);

  // non-existent attrRefs will be caught by parser
}

TEST_CASE("IntermediateTable - isColExists - SynonymRes") {
  IntermediateTable multiColSynResTable2 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_MULTI_COL_NAME_2, MULTI_COL_SYNONYM_RES_DATA_2);
  REQUIRE(multiColSynResTable2.isColExists("var"));
  REQUIRE(multiColSynResTable2.isColExists("proc"));
}

TEST_CASE(
    "IntermediateTable - getSharedColNames, getSharedColIndexes - SynonymRes") {
  IntermediateTable doubleColumnSynResTable2 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_2, DOUBLE_COL_SYNONYM_RES_DATA_2);
  IntermediateTable multiColSynResTable2 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_MULTI_COL_NAME_2, MULTI_COL_SYNONYM_RES_DATA_2);
  REQUIRE(IntermediateTableUtils::getSharedColNames(doubleColumnSynResTable2,
                                                    multiColSynResTable2) ==
          SYNONYM_RES_COL_NAME_2);
  vector<int> sharedColIndex1 = {0, 1};
  vector<int> sharedColIndex2 = {0, 3};
  REQUIRE(IntermediateTableUtils::getSharedColIndexes(doubleColumnSynResTable2,
                                                      multiColSynResTable2) ==
          pair(sharedColIndex1, sharedColIndex2));
}

TEST_CASE("IntermediateTable - join_cross - SynonymRes") {
  IntermediateTable doubleColumnSynResTable1 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_1, DOUBLE_COL_SYNONYM_RES_DATA);
  IntermediateTable doubleColumnSynResTable2 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_2, DOUBLE_COL_SYNONYM_RES_DATA_2);

  IntermediateTable crossTable =
      doubleColumnSynResTable1.join(doubleColumnSynResTable2);
  TableDataType expected = DOUBLE_COL_SYNONYM_RES_DATA_CROSS;
  const TableDataType& actual = crossTable.getTableData();

  REQUIRE(expected.size() == actual.size());
  REQUIRE(isTableDataSame(expected, actual));
}

TEST_CASE("IntermediateTable - join_inner_join - SynonymRes") {
  IntermediateTable multiColSynResTable1 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_MULTI_COL_NAME_1, MULTI_COL_SYNONYM_RES_DATA_1);

  IntermediateTable multiColSynResTable2 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_MULTI_COL_NAME_2, MULTI_COL_SYNONYM_RES_DATA_2);
  IntermediateTable joinTable = multiColSynResTable1.join(multiColSynResTable2);
  REQUIRE(isTableDataSame(joinTable.getTableData(),
                          MULTI_COL_SYNONYM_RES_DATA_INNER_JOIN));
}

TEST_CASE("IntermediateTable - join_inner_join_on - SynonymRes") {
  IntermediateTable doubleColumnSynResTable1 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_1, DOUBLE_COL_SYNONYM_RES_DATA);
  IntermediateTable doubleColumnSynResTable3 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_3, DOUBLE_COL_SYNONYM_RES_DATA_3);

  IntermediateTable joinTable = doubleColumnSynResTable1.join(
      doubleColumnSynResTable3, {"calls", ATTR_REF_PROC_NAME},
      {"print", ATTR_REF_VAR_NAME});
  TableDataType expected = {
      {MOCK_CONSTANT_SYN_1, MOCK_PRINT_SYN_1, MOCK_CONSTANT_SYN_2,
       MOCK_PRINT_SYN_2},
      {MOCK_CONSTANT_SYN_2, MOCK_PRINT_SYN_2, MOCK_CONSTANT_SYN_2,
       MOCK_PRINT_SYN_2},
  };
  REQUIRE(isTableDataSame(joinTable.getTableData(), expected));
}

TEST_CASE("IntermediateTable - join - any_x_empty - SynonymRes") {
  IntermediateTable doubleColumnSynResTable1 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_1, DOUBLE_COL_SYNONYM_RES_DATA);

  IntermediateTable doubleColumnSynResTable2 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_2, DOUBLE_COL_SYNONYM_RES_DATA_2);

  IntermediateTable doubleColumnSynResTable3 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_3, DOUBLE_COL_SYNONYM_RES_DATA_3);

  IntermediateTable multiColSynResTable1 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_MULTI_COL_NAME_1, MULTI_COL_SYNONYM_RES_DATA_1);

  IntermediateTable multiColSynResTable2 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_MULTI_COL_NAME_2, MULTI_COL_SYNONYM_RES_DATA_2);

  // data x EMPTY
  IntermediateTable empty1 =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  IntermediateTable dataJoinEmptyTable = multiColSynResTable1.join(empty1);
  REQUIRE(dataJoinEmptyTable.isTableEmptyAndNotWildcard());
  REQUIRE(dataJoinEmptyTable.getColNames().empty());

  // EMPTY x data
  IntermediateTable empty2 =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  IntermediateTable emptyJoinDataTable = empty2.join(multiColSynResTable2);
  REQUIRE(emptyJoinDataTable.isTableEmptyAndNotWildcard());
  REQUIRE(emptyJoinDataTable.getColNames().empty());

  // WILDCARD X EMPTY
  IntermediateTable wildcard1 =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  IntermediateTable empty3 =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  IntermediateTable wildcardJoinEmptyTable = wildcard1.join(empty3);
  REQUIRE(wildcardJoinEmptyTable.isTableEmptyAndNotWildcard());
  REQUIRE(wildcardJoinEmptyTable.getColNames().empty());

  // EMPTY X WILDCARD
  IntermediateTable wildcard2 =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  IntermediateTable empty4 =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  IntermediateTable emptyJoinWildcardTable = empty4.join(wildcard2);
  REQUIRE(emptyJoinWildcardTable.isTableEmpty());
  REQUIRE(emptyJoinWildcardTable.getColNames().empty());

  // EMPTY X EMPTY
  IntermediateTable empty5 =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  IntermediateTable empty6 =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  IntermediateTable emptyJoinEmptyTable = empty5.join(empty6);
  REQUIRE(emptyJoinEmptyTable.isTableEmptyAndNotWildcard());
  REQUIRE(emptyJoinEmptyTable.getColNames().empty());
}

TEST_CASE("IntermediateTable - join - any_x_wildcard - SynonymRes") {
  IntermediateTable doubleColumnSynResTable1 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_1, DOUBLE_COL_SYNONYM_RES_DATA);
  IntermediateTable doubleColumnSynResTable2 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_2, DOUBLE_COL_SYNONYM_RES_DATA_2);
  IntermediateTable doubleColumnSynResTable3 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_COL_NAME_3, DOUBLE_COL_SYNONYM_RES_DATA_3);
  IntermediateTable multiColSynResTable1 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_MULTI_COL_NAME_1, MULTI_COL_SYNONYM_RES_DATA_1);
  IntermediateTable multiColSynResTable2 =
      IntermediateTableFactory::buildIntermediateTable(
          SYNONYM_RES_MULTI_COL_NAME_2, MULTI_COL_SYNONYM_RES_DATA_2);

  IntermediateTable wildcard =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  // DATA X WILDCARD
  IntermediateTable dataJoinWildcardTable = multiColSynResTable1.join(wildcard);
  REQUIRE(dataJoinWildcardTable.isTableWildcard() == false);
  REQUIRE(isTableDataSame(dataJoinWildcardTable.getTableData(),
                          MULTI_COL_SYNONYM_RES_DATA_1));

  // WILDCARD X DATA
  IntermediateTable wildcard2 =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  IntermediateTable wildcardJoinDataTable =
      wildcard2.join(multiColSynResTable2);
  REQUIRE(wildcardJoinDataTable.isTableWildcard() == false);
  REQUIRE(isTableDataSame(wildcardJoinDataTable.getTableData(),
                          MULTI_COL_SYNONYM_RES_DATA_2));

  // WILDCARD X WILDCARD
  IntermediateTable wildcard3 =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  IntermediateTable wildcard4 =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  IntermediateTable wildcardJoinWildcardTable = wildcard4.join(wildcard3);
  REQUIRE(wildcardJoinWildcardTable.isTableWildcard() == true);

  // WILDCARD X EMPTY and vice versa is already
  // tested in "any_x_empty" tests
}
