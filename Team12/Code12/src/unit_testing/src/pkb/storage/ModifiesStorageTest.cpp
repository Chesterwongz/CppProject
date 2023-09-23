#include "catch.hpp"
#include "../../../../spa/src/pkb/storage/ModifiesStorage.h"

TEST_CASE("ModifiesStorage Tests") {
    ModifiesStorage storage;

    storage.setVariableModification("x", 1);
    storage.setVariableModification("y", 2);
    storage.setVariableModification("x", 3);
    storage.setVariableModification("z", 4);
    storage.setVariableModification("y", 5);
    storage.setVariableModification("extra_var", 1);

    SECTION("Test Getting Variable Modification") {
        REQUIRE(storage.getStatementNumbersForVariable("x") == std::set<int>{1, 3});
        REQUIRE(storage.getStatementNumbersForVariable("y") == std::set<int>{2, 5});
        REQUIRE(storage.getStatementNumbersForVariable("z") == std::set<int>{4});
        REQUIRE(storage.getStatementNumbersForVariable("a") == std::set<int>{});
    }

    SECTION("Test getting variables modified in a particular statement") {
        REQUIRE(storage.getVariablesForStatement(1) == std::set<std::string>{"x", "extra_var"});
        REQUIRE(storage.getVariablesForStatement(2) == std::set<std::string>{"y"});
        REQUIRE(storage.getVariablesForStatement(3) == std::set<std::string>{"x"});
        REQUIRE(storage.getVariablesForStatement(4) == std::set<std::string>{"z"});
        REQUIRE(storage.getVariablesForStatement(6) == std::set<std::string>{});
    }

    SECTION("Test getAllVariables and getAllStatements") {
        REQUIRE(storage.getAllVariables() == std::set<std::string>{"x", "y", "z", "extra_var"});
        REQUIRE(storage.getAllStatements() == std::set<int>{1, 2, 3, 4, 5});
    }
}