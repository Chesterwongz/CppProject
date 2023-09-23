#include <iostream>
#include "IntermediateTableTestUtils.h"
#include "IntermediateTableTestData.h"

#include "catch.hpp"
#include "qps/intermediateTable/IntermediateTableUtils.h"

IntermediateTable DOUBLE_COLUMN_TABLE_FROM_PAIR_1 = IntermediateTable(
        COL_NAME_1,
        COL_NAME_2,
        PAIR_DATA);

IntermediateTable DOUBLE_COLUMN_TABLE_FROM_PAIR_2 = IntermediateTable(
        COL_NAME_2,
        COL_NAME_1,
        PAIR_DATA);

IntermediateTable DOUBLE_COLUMN_TABLE_FROM_VECTORS_1 = IntermediateTable(
        DOUBLE_COL_NAME_VECTOR,
        DOUBLE_COL_VECTOR_DATA);

IntermediateTable DOUBLE_COLUMN_TABLE_FROM_VECTORS_2 = IntermediateTable(
        doubleColNameVector2,
        DOUBLE_COL_VECTOR_DATA_2);

IntermediateTable MULTI_COLUMN_TABLE_1 = IntermediateTable(
        MULTI_COL_NAME_VECTOR_1,
        MULTI_COL_DATA_1);

IntermediateTable MULTI_COLUMN_TABLE_2 = IntermediateTable(
        MULTI_COL_NAME_VECTOR_2,
        MULTI_COL_DATA_2);

IntermediateTable WILDCARD_TABLE = IntermediateTable::makeWildcardTable();

IntermediateTable EMPTY_TABLE = IntermediateTable::makeEmptyTable();

TEST_CASE("IntermediateTable - constructors + getData") {
    REQUIRE(isVectorsSameAsPairs(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.getData(), PAIR_DATA));
    REQUIRE(isVectorsSameAsPairs(DOUBLE_COLUMN_TABLE_FROM_VECTORS_1.getData(), PAIR_DATA));
    std::cout << "expect \"row 0 incorrect\":" << std::endl;
    REQUIRE(isVectorsSameAsPairs(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2.getData(), PAIR_DATA) == false);

    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.getData() == DOUBLE_COLUMN_TABLE_FROM_VECTORS_1.getData());
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.getData() == DOUBLE_COL_VECTOR_DATA);
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_VECTORS_1.getData() == DOUBLE_COL_VECTOR_DATA);
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2.getData() == DOUBLE_COL_VECTOR_DATA_2);
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

TEST_CASE("IntermediateTable - getCol") {
    // get column 1
    vector<string> vectorWithColName1 = {COL_NAME_1};
    vector<vector<string>> vectorWithCol1 = COL_1_2D;
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.getCol(vectorWithColName1) == vectorWithCol1);

    // get column 2
    vector<string> vectorWithColName2 = {COL_NAME_2};
    vector<vector<string>> vectorWithCol2 = COL_2_2D;
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.getCol(vectorWithColName2) == vectorWithCol2);

    // get both columns
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.getCol(DOUBLE_COL_NAME_VECTOR) == DOUBLE_COL_VECTOR_DATA);
}

TEST_CASE("IntermediateTable - getSingleCol") {
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.getSingleCol(COL_NAME_1) == COL_1);
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.getSingleCol(COL_NAME_2) == COL_2);
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2.getSingleCol(COL_NAME_3) == COL_3);
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2.getSingleCol(COL_NAME_4) == COL_4);

    // non-existent column name
    REQUIRE_THROWS(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.getSingleCol(COL_NAME_3));
}

TEST_CASE("IntermediateTable - isColExists") {
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.isColExists(COL_NAME_1));
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.isColExists(COL_NAME_2));
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.isColExists(COL_NAME_3) == false);
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR_1.isColExists(COL_NAME_4) == false);
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2.isColExists(COL_NAME_3));
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2.isColExists(COL_NAME_4));

    auto newTable = DOUBLE_COLUMN_TABLE_FROM_VECTORS_1.join(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2);
}

TEST_CASE("IntermediateTable - getSharedColNames, getSharedColIndexes") {
    REQUIRE(getSharedColNames(
            DOUBLE_COLUMN_TABLE_FROM_PAIR_1,
            MULTI_COLUMN_TABLE_1) == DOUBLE_COL_NAME_VECTOR);
    vector<int> sharedColIndex1 = {0, 1};
    vector<int> sharedColIndex2 = {3, 2};
    REQUIRE(getSharedColIndexes(
            DOUBLE_COLUMN_TABLE_FROM_PAIR_1,
            MULTI_COLUMN_TABLE_1) == pair(sharedColIndex1, sharedColIndex2));
}

TEST_CASE("IntermediateTable - join - cross") {
    IntermediateTable crossTable =
            DOUBLE_COLUMN_TABLE_FROM_VECTORS_1.join(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2);
    REQUIRE(crossTable.getData() == DOUBLE_COL_VECTOR_DATA_CROSS);
}

TEST_CASE("IntermediateTable - join - inner join") {
    IntermediateTable joinTable =
            MULTI_COLUMN_TABLE_1.join(MULTI_COLUMN_TABLE_2);
    REQUIRE(joinTable.getData() == MULTI_COL_DATA_JOIN);
}

TEST_CASE("IntermediateTable - join - any_x_empty") {
    // data x EMPTY
    IntermediateTable dataJoinEmptyTable =
            MULTI_COLUMN_TABLE_1.join(EMPTY_TABLE);
    REQUIRE(dataJoinEmptyTable.isTableEmpty());
    REQUIRE(dataJoinEmptyTable.getData().empty());

    // EMPTY x data
    IntermediateTable emptyJoinDataTable =
            EMPTY_TABLE.join(MULTI_COLUMN_TABLE_1);
    REQUIRE(emptyJoinDataTable.isTableEmpty());
    REQUIRE(emptyJoinDataTable.getData().empty());

    // WILDCARD X EMPTY
    IntermediateTable wildcardJoinEmptyTable =
            WILDCARD_TABLE.join(EMPTY_TABLE);
    REQUIRE(wildcardJoinEmptyTable.isTableEmpty());
    REQUIRE(wildcardJoinEmptyTable.getData().empty());

    // EMPTY X WILDCARD
    IntermediateTable emptyJoinWildcardTable =
            EMPTY_TABLE.join(WILDCARD_TABLE);
    REQUIRE(emptyJoinWildcardTable.isTableEmpty());
    REQUIRE(emptyJoinWildcardTable.getData().empty());

    // EMPTY X EMPTY
    IntermediateTable emptyJoinEmptyTable =
            EMPTY_TABLE.join(EMPTY_TABLE);
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

