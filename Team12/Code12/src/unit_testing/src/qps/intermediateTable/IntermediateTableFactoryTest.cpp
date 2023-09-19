#include <iostream>
#include "catch.hpp"
#include "qps/intermediateTable/IntermediateTableFactory.h"
#include "TestIntermediateTableData.h"
#include "TestIntermediateTableUtils.h"

TEST_CASE("IntermediateTableFactory - buildIntermediateTable - pairs_without_wildcard") {
    IntermediateTable tableFromPairs = IntermediateTableFactory::buildIntermediateTable(
            COL_NAME_1,
            COL_NAME_2,
            PAIR_DATA);
    REQUIRE(isVectorsSameAsPairs(tableFromPairs.getData(), PAIR_DATA));
    REQUIRE(tableFromPairs.isTableEmpty() == false);
    REQUIRE(tableFromPairs.isTableEmptyAndNotWildcard() == false);
    REQUIRE(tableFromPairs.isTableWildcard() == false);
}

TEST_CASE("IntermediateTableFactory - buildIntermediateTable - pairs_with_wildcard") {
    IntermediateTable tableFromPairsWithWildcard1 = IntermediateTableFactory::buildIntermediateTable(
            COL_NAME_1,
            COL_NAME_WILDCARD,
            PAIR_DATA);
    REQUIRE(tableFromPairsWithWildcard1.getData() == COL_1_2D);
    REQUIRE(tableFromPairsWithWildcard1.isTableEmpty() == false);
    REQUIRE(tableFromPairsWithWildcard1.isTableEmptyAndNotWildcard() == false);
    REQUIRE(tableFromPairsWithWildcard1.isTableWildcard() == false);
    REQUIRE(tableFromPairsWithWildcard1.getData().at(0).size() == 1);

    IntermediateTable tableFromPairsWithWildcard2 = IntermediateTableFactory::buildIntermediateTable(
            COL_NAME_WILDCARD,
            COL_NAME_2,
            PAIR_DATA);
    REQUIRE(tableFromPairsWithWildcard2.getData() == COL_2_2D);
    REQUIRE(tableFromPairsWithWildcard2.isTableEmpty() == false);
    REQUIRE(tableFromPairsWithWildcard2.isTableEmptyAndNotWildcard() == false);
    REQUIRE(tableFromPairsWithWildcard2.isTableWildcard() == false);
    REQUIRE(tableFromPairsWithWildcard2.getData().at(0).size() == 1);
}

TEST_CASE("IntermediateTableFactory - buildIntermediateTable - vectors_without_wildcard") {
    IntermediateTable tableFromVectors = IntermediateTableFactory::buildIntermediateTable(
            MULTI_COL_NAME_VECTOR_1,
            MULTI_COL_DATA_1);
    REQUIRE(tableFromVectors.getData() == MULTI_COL_DATA_1);
    REQUIRE(tableFromVectors.isTableEmpty() == false);
    REQUIRE(tableFromVectors.isTableEmptyAndNotWildcard() == false);
    REQUIRE(tableFromVectors.isTableWildcard() == false);
}

TEST_CASE("IntermediateTableFactory - buildIntermediateTable - vectors_with_wildcard") {
    IntermediateTable tableFromVectorsWithWildcard = IntermediateTableFactory::buildIntermediateTable(
            MULTI_COL_NAME_VECTOR_WITH_WILDCARD,
            MULTI_COL_DATA_1);
    REQUIRE(tableFromVectorsWithWildcard.getData() == MULTI_COL_DATA_1_WILDCARD);
    REQUIRE(tableFromVectorsWithWildcard.isTableEmpty() == false);
    REQUIRE(tableFromVectorsWithWildcard.isTableEmptyAndNotWildcard() == false);
    REQUIRE(tableFromVectorsWithWildcard.isTableWildcard() == false);
    REQUIRE(tableFromVectorsWithWildcard.getData().at(0).size() == 3);
}

TEST_CASE("IntermediateTableFactory - buildEmptyTable") {
    IntermediateTable emptyTable = IntermediateTableFactory::buildEmptyIntermediateTable();
    REQUIRE(emptyTable.isTableEmpty());
    REQUIRE(emptyTable.isTableEmptyAndNotWildcard());
    REQUIRE(emptyTable.isTableWildcard() == false);
    REQUIRE(emptyTable.getData().empty());
}

TEST_CASE("IntermediateTableFactory - buildWildcardTable") {
    IntermediateTable wildcardTable = IntermediateTableFactory::buildWildcardIntermediateTable();
    REQUIRE(wildcardTable.isTableWildcard());
    REQUIRE(wildcardTable.isTableEmpty());
    REQUIRE(wildcardTable.isTableEmptyAndNotWildcard() == false);
    REQUIRE(wildcardTable.getData().empty());
}
