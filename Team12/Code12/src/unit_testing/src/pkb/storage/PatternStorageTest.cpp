#include "catch.hpp"
#include "../../../../spa/src/pkb/storage/PatternStorage.h"

TEST_CASE("PatternStorage Tests") {
    PatternStorage patternStorage;

    patternStorage.setAssignPattern("x", "abc*+", 1); // "a+b*c"
    patternStorage.setAssignPattern("y", "de+f+", 2); // "d+e+f"
    patternStorage.setAssignPattern("z", "ab*c*d+", 3); // "a*b*c+d"
    patternStorage.setAssignPattern("x", "a2+", 4); // "a+2"
    patternStorage.setAssignPattern("x", "abc*+", 5); // "a+b*c"

    SECTION("setAssignPattern and getAllStatements") {
        REQUIRE(patternStorage.getAllStatements() == std::vector<std::string>{"1", "2", "3", "4", "5"});
    }

    SECTION("getAllStatementsWithVariable") {
        REQUIRE(patternStorage.getAllStatementsWithVariable("x") == std::vector<std::string>{"1", "4", "5"});
        REQUIRE(patternStorage.getAllStatementsWithVariable("y") == std::vector<std::string>{"2"});
        REQUIRE(patternStorage.getAllStatementsWithVariable("z") == std::vector<std::string>{"3"});
        REQUIRE(patternStorage.getAllStatementsWithVariable("_") == std::vector<std::string>{"1", "2", "3", "4", "5"});
        REQUIRE(patternStorage.getAllStatementsWithVariable("w") == std::vector<std::string>{});
    }

    SECTION("getExactAssignPattern") {
        REQUIRE(patternStorage.getExactAssignPattern("x", "abc*+", false) == std::vector<std::string>{"1", "5"});
        REQUIRE(patternStorage.getExactAssignPattern("x", "b", false) == std::vector<std::string>{});
        REQUIRE(patternStorage.getExactAssignPattern("y", "de+f+", false) == std::vector<std::string>{"2"});
        REQUIRE(patternStorage.getExactAssignPattern("z", "abc*+", false) == std::vector<std::string>{});
        REQUIRE(patternStorage.getExactAssignPattern("v", "abc*+", true) == std::vector<std::string>{"1", "5"});
        REQUIRE(patternStorage.getExactAssignPattern("_", "_", false) == std::vector<std::string>{"1", "2", "3", "4", "5"});
        REQUIRE(patternStorage.getExactAssignPattern("x", "_", false) == std::vector<std::string>{"1", "4", "5"});
        REQUIRE(patternStorage.getExactAssignPattern("_", "abc*+", false) == std::vector<std::string>{"1", "5"});
    }

    SECTION("getPartialAssignPattern") {
        REQUIRE(patternStorage.getPartialAssignPattern("x", "abc*+", false) == std::vector<std::string>{"1", "5"});
        REQUIRE(patternStorage.getPartialAssignPattern("x", "2", false) == std::vector<std::string>{"4"});
        REQUIRE(patternStorage.getPartialAssignPattern("x", "3", false) == std::vector<std::string>{});
        REQUIRE(patternStorage.getPartialAssignPattern("y", "f", false) == std::vector<std::string>{"2"});
        REQUIRE(patternStorage.getPartialAssignPattern("_", "a", false) == std::vector<std::string>{"1", "3", "4", "5"});
        REQUIRE(patternStorage.getPartialAssignPattern("v", "a", true) == std::vector<std::string>{"1", "3", "4", "5"});
        REQUIRE(patternStorage.getPartialAssignPattern("x", "_", false) == std::vector<std::string>{"1", "4", "5"});
        REQUIRE(patternStorage.getPartialAssignPattern("v", "_", true) == std::vector<std::string>{"1", "2", "3", "4", "5"});
        REQUIRE(patternStorage.getPartialAssignPattern("_", "_", false) == std::vector<std::string>{"1", "2", "3", "4", "5"});
    }
}