#include "catch.hpp"
#include "../../../../spa/src/pkb/storage/DesignEntitiesStorage.h"

TEST_CASE("DesignEntitiesStorage Tests") {

    DesignEntitiesStorage storage;

    SECTION("Set and Get Variables") {
        storage.setVariable("x");
        storage.setVariable("y");
        storage.setVariable("z");

        REQUIRE(storage.getAllVariables() == std::set<std::string>{"x", "y", "z"});
    }

    SECTION("Set and Get Constants") {
        storage.setConstant("5");
        storage.setConstant("10");

        REQUIRE(storage.getAllConstants() == std::set<std::string>{"5", "10"});
    }

    SECTION("Set and Get Procedures") {
        storage.setProcedure("proc1", 1);
        storage.setProcedure("proc2", 5);

        REQUIRE(storage.getAllProcedures() == std::set<std::string>{"proc1", "proc2"});
    }

    SECTION("Get Procedure Starting on Statement") {
        storage.setProcedure("proc1", 1);
        storage.setProcedure("proc2", 5);

        REQUIRE(storage.getProcedureStartingOnStatement(1) == "proc1");
        REQUIRE(storage.getProcedureStartingOnStatement(5) == "proc2");
        REQUIRE(storage.getProcedureStartingOnStatement(3) == "");
    }
}