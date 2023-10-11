#include <catch.hpp>

#include "pkb/storage/relation_storage/stmt_or_proc_to_var/ModifiesStorage.h"

TEST_CASE("ModifiesStorage Tests") {
  ModifiesStorage storage;

  storage.addModifies("x", 1);
  storage.addModifies("y", 2);
  storage.addModifies("x", 3);
  storage.addModifies("z", 4);
  storage.addModifies("y", 5);
  storage.addModifies("extra_var", 1);

  SECTION("Test Getting Variable Modification") {
    REQUIRE(storage.getStmtsModifyingVar("x") == std::set<int>{1, 3});
    REQUIRE(storage.getStmtsModifyingVar("y") == std::set<int>{2, 5});
    REQUIRE(storage.getStmtsModifyingVar("z") == std::set<int>{4});
    REQUIRE(storage.getStmtsModifyingVar("a") == std::set<int>{});
  }

  SECTION("Test getting variables modified in a particular statement") {
    REQUIRE(storage.getVarsModifiedByStmt(1) ==
            std::set<std::string>{"x", "extra_var"});
    REQUIRE(storage.getVarsModifiedByStmt(2) == std::set<std::string>{"y"});
    REQUIRE(storage.getVarsModifiedByStmt(3) == std::set<std::string>{"x"});
    REQUIRE(storage.getVarsModifiedByStmt(4) == std::set<std::string>{"z"});
    REQUIRE(storage.getVarsModifiedByStmt(6) == std::set<std::string>{});
  }

  SECTION("Test getAllVarUsedByStmt and getAllStmtUsingVar") {
    REQUIRE(storage.getAllVarsModifiedByStmt() ==
            std::set<std::string>{"x", "y", "z", "extra_var"});
    REQUIRE(storage.getAllStmtsModifyingVar() == std::set<int>{1, 2, 3, 4, 5});
  }
}
