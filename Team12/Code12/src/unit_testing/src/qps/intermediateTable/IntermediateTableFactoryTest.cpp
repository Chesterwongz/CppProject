#include <catch.hpp>

#include "IntermediateTableTestUtils.h"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "testData/StringTestData.h"
#include "testData/SynonymResTestData.h"

TEST_CASE(
    "IntermediateTableFactory - buildIntermediateTable - "
    "pairs_without_wildcard") {
  IntermediateTable tableFromPairs =
      IntermediateTableFactory::buildIntermediateTable(COL_NAME_1, COL_NAME_2,
                                                       PAIR_DATA);
  REQUIRE(isVectorsSameAsPairs(tableFromPairs.getDataAsStrings(), PAIR_DATA));
  REQUIRE(tableFromPairs.isTableEmpty() == false);
  REQUIRE(tableFromPairs.isTableEmptyAndNotWildcard() == false);
  REQUIRE(tableFromPairs.isTableWildcard() == false);
}

TEST_CASE(
    "IntermediateTableFactory - buildIntermediateTable - pairs_with_wildcard") {
  IntermediateTable tableFromPairsWithWildcard1 =
      IntermediateTableFactory::buildIntermediateTable(
          COL_NAME_1, COL_NAME_WILDCARD, PAIR_DATA);
  REQUIRE(tableFromPairsWithWildcard1.getDataAsStrings() == COL_1_2D);
  REQUIRE(tableFromPairsWithWildcard1.isTableEmpty() == false);
  REQUIRE(tableFromPairsWithWildcard1.isTableEmptyAndNotWildcard() == false);
  REQUIRE(tableFromPairsWithWildcard1.isTableWildcard() == false);
  REQUIRE(tableFromPairsWithWildcard1.getDataAsStrings().at(0).size() == 1);

  IntermediateTable tableFromPairsWithWildcard2 =
      IntermediateTableFactory::buildIntermediateTable(COL_NAME_WILDCARD,
                                                       COL_NAME_2, PAIR_DATA);
  REQUIRE(tableFromPairsWithWildcard2.getDataAsStrings() == COL_2_2D);
  REQUIRE(tableFromPairsWithWildcard2.isTableEmpty() == false);
  REQUIRE(tableFromPairsWithWildcard2.isTableEmptyAndNotWildcard() == false);
  REQUIRE(tableFromPairsWithWildcard2.isTableWildcard() == false);
  REQUIRE(tableFromPairsWithWildcard2.getDataAsStrings().at(0).size() == 1);
}

TEST_CASE(
    "IntermediateTableFactory - buildIntermediateTable - "
    "vectors_without_wildcard") {
  IntermediateTable tableFromVectors =
      IntermediateTableFactory::buildIntermediateTable(
          MULTI_COL_NAME_VECTOR_1, convertToSynonymResCol(MULTI_COL_DATA_1));
  REQUIRE(tableFromVectors.getDataAsStrings() == MULTI_COL_DATA_1);
  REQUIRE(tableFromVectors.isTableEmpty() == false);
  REQUIRE(tableFromVectors.isTableEmptyAndNotWildcard() == false);
  REQUIRE(tableFromVectors.isTableWildcard() == false);
}

TEST_CASE(
    "IntermediateTableFactory - buildIntermediateTable - "
    "vectors_with_wildcard") {
  IntermediateTable tableFromVectorsWithWildcard =
      IntermediateTableFactory::buildIntermediateTable(
          MULTI_COL_NAME_VECTOR_WITH_WILDCARD,
          convertToSynonymResCol(MULTI_COL_DATA_1));
  REQUIRE(tableFromVectorsWithWildcard.getDataAsStrings() ==
          MULTI_COL_DATA_1_WILDCARD);
  REQUIRE(tableFromVectorsWithWildcard.isTableEmpty() == false);
  REQUIRE(tableFromVectorsWithWildcard.isTableEmptyAndNotWildcard() == false);
  REQUIRE(tableFromVectorsWithWildcard.isTableWildcard() == false);
  REQUIRE(tableFromVectorsWithWildcard.getDataAsStrings().at(0).size() == 3);
}

TEST_CASE(
    "IntermediateTableFactory - buildIntermediateTable - "
    "from_synonymRes_vs_from_string") {
  IntermediateTable tableFromString =
      IntermediateTableFactory::buildIntermediateTable(
          MULTI_COL_NAME_VECTOR_WITH_WILDCARD,
          convertToSynonymResCol(MULTI_COL_DATA_1));
  IntermediateTable tableFromSynonymRes =
      IntermediateTableFactory::buildIntermediateTable(
          MULTI_COL_NAME_VECTOR_WITH_WILDCARD,
          convertToSynonymResCol(MULTI_COL_DATA_1));

  REQUIRE(tableFromString.getDataAsStrings() ==
          tableFromSynonymRes.getDataAsStrings());
  REQUIRE(isTableDataSame(tableFromString.getTableData(),
                          tableFromSynonymRes.getTableData()));
  REQUIRE(tableFromString.getColNames() == tableFromSynonymRes.getColNames());
}

TEST_CASE("IntermediateTableFactory - buildSingleColTable - from_synonymRes") {
  IntermediateTable table = IntermediateTableFactory::buildSingleColTable(
      COL_NAME_1, MOCK_PRINT_SYNONYM_RES_VECTOR);
  REQUIRE(table.getDataAsStrings() == MOCK_SYNONYM_RES_VALUES_VECTOR_2D);
  REQUIRE(
      isTableDataSame(table.getTableData(), MOCK_PRINT_SYNONYM_RES_VECTOR_2D));
  REQUIRE_FALSE(table.isTableWildcard());
  REQUIRE_FALSE(table.isTableEmptyAndNotWildcard());
}

TEST_CASE("IntermediateTableFactory - buildSingleColTable - wildcard") {
  IntermediateTable table = IntermediateTableFactory::buildSingleColTable(
      WILDCARD_KEYWORD, MOCK_PRINT_SYNONYM_RES_VECTOR);
  REQUIRE(table.isTableWildcard());
}

TEST_CASE("IntermediateTableFactory - buildIntermediateTable - singleton") {
  IntermediateTable singletonTable =
      IntermediateTableFactory::buildIntermediateTable(
          COL_NAME_3, SynonymResFactory::buildDefaultSynonym(COL_SINGLETON));
  REQUIRE(singletonTable.getDataAsStrings() == COL_SINGLETON_2D);
  REQUIRE(singletonTable.isTableEmpty() == false);
  REQUIRE(singletonTable.isTableEmptyAndNotWildcard() == false);
  REQUIRE(singletonTable.isTableWildcard() == false);
  REQUIRE(singletonTable.getDataAsStrings().size() == 1);
  REQUIRE(singletonTable.getDataAsStrings().at(0).size() == 1);
}

TEST_CASE(
    "IntermediateTableFactory - buildIntermediateTable - singleton wildcard") {
  IntermediateTable tableFromVectorsWithWildcard =
      IntermediateTableFactory::buildIntermediateTable(
          WILDCARD_KEYWORD,
          SynonymResFactory::buildDefaultSynonym(COL_SINGLETON));
  REQUIRE(tableFromVectorsWithWildcard.isTableWildcard());
}

TEST_CASE("IntermediateTableFactory - buildEmptyTable") {
  IntermediateTable emptyTable =
      IntermediateTableFactory::buildEmptyIntermediateTable();
  REQUIRE(emptyTable.isTableEmpty());
  REQUIRE(emptyTable.isTableEmptyAndNotWildcard());
  REQUIRE(emptyTable.isTableWildcard() == false);
  REQUIRE(emptyTable.getDataAsStrings().empty());
}

TEST_CASE("IntermediateTableFactory - buildWildcardTable") {
  IntermediateTable wildcardTable =
      IntermediateTableFactory::buildWildcardIntermediateTable();
  REQUIRE(wildcardTable.isTableWildcard());
  REQUIRE(wildcardTable.isTableEmpty());
  REQUIRE(wildcardTable.isTableEmptyAndNotWildcard() == false);
  REQUIRE(wildcardTable.getDataAsStrings().empty());
}
