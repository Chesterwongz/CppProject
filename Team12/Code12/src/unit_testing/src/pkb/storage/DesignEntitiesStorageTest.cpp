#include <unordered_set>
#include <catch.hpp>

#include "pkb/storage/entity_storage/EntityStore.h"

TEST_CASE("DesignEntitiesStorage Tests") {
  EntityStore storage;

  storage.addProc("proc1");
  storage.addProc("proc2");
  storage.addProc("proc2");

  SECTION("Set and Get Variables") {
    storage.addVar("x");
    storage.addVar("y");
    storage.addVar("z");

    REQUIRE(storage.getAllVars() ==
            std::unordered_set<std::string> {"x", "y", "z"});
  }

  SECTION("Set and Get Constants") {
    storage.addConst("5");
    storage.addConst("10");

    REQUIRE(storage.getAllConsts() ==
            std::unordered_set<std::string> {"5", "10"});
  }

  SECTION("Get Procedures") {
    REQUIRE(storage.getAllProcs() ==
            std::unordered_set<std::string> {"proc1", "proc2"});
  }
}
