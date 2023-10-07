//
//
// // TEMP_CATCH_INCLUDE
// #include "../../spa/src/Storage.h"
// #include <vector>
// #include <string>
// #include <stdexcept>
//
// using namespace std;
//
// TEST_CASE("Table functionality tests") {
//    Storage myTable;
//
//    SECTION("Insert rows and retrieve second column") {
//        myTable.insertRow(1, "Row 1");
//        myTable.insertRow(2, "Row 2");
//        myTable.insertRow(3, "Row 3");
//
//        REQUIRE(myTable.getSecondColumnByFirstColumn(1) == "Row 1");
//        REQUIRE(myTable.getSecondColumnByFirstColumn(2) == "Row 2");
//        REQUIRE(myTable.getSecondColumnByFirstColumn(3) == "Row 3");
//    }
//
//    SECTION("Calculate the number of rows") {
//        REQUIRE(myTable.getRowCount() == 0);
//
//        myTable.insertRow(1, "Row 1");
//        myTable.insertRow(2, "Row 2");
//        myTable.insertRow(3, "Row 3");
//
//        REQUIRE(myTable.getRowCount() == 3);
//    }
//
//    SECTION("Retrieve second column with non-existent first column value") {
//        myTable.insertRow(1, "Row 1");
//
//        // Check for an exception when the row is not found
//        REQUIRE_THROWS_WITH(
//            myTable.getSecondColumnByFirstColumn(2),
//            "Row not found"
//        );
//    }
// }
