#include <catch.hpp>

#include "pkb/storage/relation_storage/stmt_proc_to_var/UsesStorage.h"

TEST_CASE("UsesStorage Tests") {
  UsesStorage storage;

  storage.addUses("x", 1);
  storage.addUses("y", 1);
  storage.addUses("x", 2);
  storage.addUses("z", 3);
  storage.addUses("x", 4);

  SECTION("Test Getting Variable Usage") {
    REQUIRE(storage.getStmtsUsingVar("x") == std::set<int>{1, 2, 4});
    REQUIRE(storage.getStmtsUsingVar("y") == std::set<int>{1});
    REQUIRE(storage.getStmtsUsingVar("z") == std::set<int>{3});
    REQUIRE(storage.getStmtsUsingVar("a") == std::set<int>{});
  }

  SECTION("Test getting variables used in a particular statement") {
    REQUIRE(storage.getVarsUsedByStmt(1) == std::set<std::string>{"x", "y"});
    REQUIRE(storage.getVarsUsedByStmt(2) == std::set<std::string>{"x"});
    REQUIRE(storage.getVarsUsedByStmt(3) == std::set<std::string>{"z"});
    REQUIRE(storage.getVarsUsedByStmt(4) == std::set<std::string>{"x"});
    REQUIRE(storage.getVarsUsedByStmt(6) == std::set<std::string>{});
  }

  SECTION("Test getAllVarUsedByStmt and getAllStmtUsingVar") {
    REQUIRE(storage.getAllVarUsedByStmt() ==
            std::set<std::string>{"x", "y", "z"});
    REQUIRE(storage.getAllStmtUsingVar() == std::set<int>{1, 2, 3, 4});
  }
}
