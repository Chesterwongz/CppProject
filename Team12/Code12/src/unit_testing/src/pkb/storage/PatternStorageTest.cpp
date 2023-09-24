#include "catch.hpp"
#include "../../../../spa/src/pkb/storage/PatternStorage.h"

TEST_CASE("PatternStorage Tests") {
    PatternStorage patternStorage;

    patternStorage.setAssignPattern("x", "a b c * +", 1); // "a+b*c"
    patternStorage.setAssignPattern("y", "d e + f +", 2); // "d+e+f"
    patternStorage.setAssignPattern("z", "a b * c * d +", 3); // "a*b*c+d"
    patternStorage.setAssignPattern("x", "a 2 +", 4); // "a+2"
    patternStorage.setAssignPattern("x", "a b c * +", 5); // "a+b*c"

    SECTION("setAssignPattern and getAllStatements") {
        REQUIRE(patternStorage.getAllStatements() == std::vector<std::string>{"5", "4", "3", "2", "1"});
    }

    SECTION("getAllStatementsWithVariable") {
        REQUIRE(patternStorage.getAllStatementsWithVariable("x") == std::vector<std::string>{"1", "4", "5"});
        REQUIRE(patternStorage.getAllStatementsWithVariable("y") == std::vector<std::string>{"2"});
        REQUIRE(patternStorage.getAllStatementsWithVariable("z") == std::vector<std::string>{"3"});
        REQUIRE(patternStorage.getAllStatementsWithVariable("w").empty());
    }

    SECTION("getExactAssignPattern") {
        REQUIRE(patternStorage.getExactAssignPattern("x", "a b c * +", false) == std::vector<std::string>{"5", "1"});
        REQUIRE(patternStorage.getExactAssignPattern("x", "b", false).empty());
        REQUIRE(patternStorage.getExactAssignPattern("y", "d e + f +", false) == std::vector<std::string>{"2"});
        REQUIRE(patternStorage.getExactAssignPattern("z", "a b c * +", false).empty());
        REQUIRE(patternStorage.getExactAssignPattern("v", "a b c * +", true) == std::vector<std::string>{"5", "1"});
        REQUIRE(patternStorage.getExactAssignPattern("_", "_", false) == std::vector<std::string>{"5", "4", "3", "2", "1"});
        REQUIRE(patternStorage.getExactAssignPattern("x", "_", false) == std::vector<std::string>{"1", "4", "5"});
        REQUIRE(patternStorage.getExactAssignPattern("_", "a b c * +", false) == std::vector<std::string>{"5", "1"});
    }

    SECTION("getPartialAssignPattern") {
        REQUIRE(patternStorage.getPartialAssignPattern("x", "a b c * +", false) == std::vector<std::string>{"5", "1"});
        REQUIRE(patternStorage.getPartialAssignPattern("x", "2", false) == std::vector<std::string>{"4"});
        REQUIRE(patternStorage.getPartialAssignPattern("x", "3", false).empty());
        REQUIRE(patternStorage.getPartialAssignPattern("y", "f", false) == std::vector<std::string>{"2"});
        REQUIRE(patternStorage.getPartialAssignPattern("_", "a", false) == std::vector<std::string>{"5", "4", "3", "1"});
        REQUIRE(patternStorage.getPartialAssignPattern("v", "a", true) == std::vector<std::string>{"5", "4", "3", "1"});
        REQUIRE(patternStorage.getPartialAssignPattern("x", "_", false) == std::vector<std::string>{"1", "4", "5"});
        REQUIRE(patternStorage.getPartialAssignPattern("v", "_", true) == std::vector<std::string>{"5", "4", "3", "2", "1"});
        REQUIRE(patternStorage.getPartialAssignPattern("_", "_", false) == std::vector<std::string>{"5", "4", "3", "2", "1"});
    }
}
