#include <iostream>
#include "TestIntermediateTableUtils.h"
#include "TestIntermediateTableData.h"

#include "catch.hpp"

IntermediateTable DOUBLE_COLUMN_TABLE_FROM_PAIR = IntermediateTable(
        COL_NAME_1,
        COL_NAME_2,
        PAIR_DATA);

IntermediateTable DOUBLE_COLUMN_TABLE_FROM_VECTORS = IntermediateTable(
        doubleColNameVector,
        DOUBLE_COL_VECTOR_DATA);

IntermediateTable DOUBLE_COLUMN_TABLE_FROM_VECTORS_2 = IntermediateTable(
        doubleColNameVector2,
        DOUBLE_COL_VECTOR_DATA_2);

TEST_CASE("IntermediateTable - constructors + getTable") {
    REQUIRE(isVectorsSameAsPairs(DOUBLE_COLUMN_TABLE_FROM_PAIR.getTable(), PAIR_DATA));
    REQUIRE(isVectorsSameAsPairs(DOUBLE_COLUMN_TABLE_FROM_VECTORS.getTable(), PAIR_DATA));
    std::cout << "expect \"row 0 incorrect\":" << std::endl;
    REQUIRE(!isVectorsSameAsPairs(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2.getTable(), PAIR_DATA));

    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR.getTable() == DOUBLE_COLUMN_TABLE_FROM_VECTORS.getTable());
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR.getTable() == DOUBLE_COL_VECTOR_DATA);
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_VECTORS.getTable() == DOUBLE_COL_VECTOR_DATA);
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_VECTORS_2.getTable() == DOUBLE_COL_VECTOR_DATA_2);
}

TEST_CASE("IntermediateTable - getSingleCol - string") {
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR.getSingleCol(COL_NAME_1) == COL_1);
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR.getSingleCol(COL_NAME_2) == COL_2);
    // non-existent column name
    REQUIRE_THROWS(DOUBLE_COLUMN_TABLE_FROM_PAIR.getSingleCol(COL_NAME_3));
}

TEST_CASE("IntermediateTable - getSingleCol - vector") {
    // get column 1
    vector<string> vectorWithColName1 = {COL_NAME_1};
    vector<vector<string>> vectorWithCol1 = COL_1_2D;
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR.getCol(vectorWithColName1) == vectorWithCol1);

    // get column 2
    vector<string> vectorWithColName2 = {COL_NAME_2};
    vector<vector<string>> vectorWithCol2 = COL_2_2D;
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR.getCol(vectorWithColName2) == vectorWithCol2);

    // get both columns
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR.getCol(doubleColNameVector) == DOUBLE_COL_VECTOR_DATA);
}

TEST_CASE("IntermediateTable - getRow") {
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR.getSingleCol(COL_NAME_1) == COL_1);
    REQUIRE(DOUBLE_COLUMN_TABLE_FROM_PAIR.getSingleCol(COL_NAME_2) == COL_2);
}
