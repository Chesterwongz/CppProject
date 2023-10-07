// TEMP_CATCH_INCLUDE

#include "../../../../spa/src/pkb/storage/UsesStorage.h"

TEST_CASE("UsesStorage Tests") {
  UsesStorage storage;

  storage.setVariableUsage("x", 1);
  storage.setVariableUsage("y", 1);
  storage.setVariableUsage("x", 2);
  storage.setVariableUsage("z", 3);
  storage.setVariableUsage("x", 4);

  SECTION("Test Getting Variable Usage") {
    REQUIRE(storage.getStatementNumbersForVariable("x") ==
            std::set<int>{1, 2, 4});
    REQUIRE(storage.getStatementNumbersForVariable("y") == std::set<int>{1});
    REQUIRE(storage.getStatementNumbersForVariable("z") == std::set<int>{3});
    REQUIRE(storage.getStatementNumbersForVariable("a") == std::set<int>{});
  }

  SECTION("Test getting variables used in a particular statement") {
    REQUIRE(storage.getVariablesForStatement(1) ==
            std::set<std::string>{"x", "y"});
    REQUIRE(storage.getVariablesForStatement(2) == std::set<std::string>{"x"});
    REQUIRE(storage.getVariablesForStatement(3) == std::set<std::string>{"z"});
    REQUIRE(storage.getVariablesForStatement(4) == std::set<std::string>{"x"});
    REQUIRE(storage.getVariablesForStatement(6) == std::set<std::string>{});
  }

  SECTION("Test getAllVariables and getAllStatements") {
    REQUIRE(storage.getAllVariables() == std::set<std::string>{"x", "y", "z"});
    REQUIRE(storage.getAllStatements() == std::set<int>{1, 2, 3, 4});
  }
}
