#include <set>
#include <catch.hpp>

#include "pkb/storage/entity_storage/DesignEntitiesStorage.h"

TEST_CASE("DesignEntitiesStorage Tests") {
  DesignEntitiesStorage storage;

  storage.setProcForStmt("proc1", 1);
  storage.setProcForStmt("proc1", 2);
  storage.setProcForStmt("proc1", 3);
  storage.setProcForStmt("proc1", 4);
  storage.setProcForStmt("proc2", 5);
  storage.setProcForStmt("proc2", 6);

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

  SECTION("Get Procedures") {
    REQUIRE(storage.getAllProcedures() ==
            std::set<std::string>{"proc1", "proc2"});
  }

  SECTION("Get Procedures from statement number") {
    REQUIRE(storage.getProcFromStmt(1) == "proc1");
    REQUIRE(storage.getProcFromStmt(2) == "proc1");
    REQUIRE(storage.getProcFromStmt(3) == "proc1");
    REQUIRE(storage.getProcFromStmt(4) == "proc1");
    REQUIRE(storage.getProcFromStmt(5) == "proc2");
    REQUIRE(storage.getProcFromStmt(6) == "proc2");
  }
}
