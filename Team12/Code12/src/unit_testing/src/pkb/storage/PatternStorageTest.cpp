#include <catch.hpp>
#include <unordered_set>

#include "../../common/utils/HelperFunctions.h"
#include "pkb/storage/pattern_storage/PatternStorage.h"

TEST_CASE("PatternStorage Tests") {
  PatternStorage patternStorage;

  patternStorage.setAssignPattern("x", " a b c * + ", 1);      // "a+b*c"
  patternStorage.setAssignPattern("y", " d e + f + ", 2);      // "d+e+f"
  patternStorage.setAssignPattern("z", " a b * c * d + ", 3);  // "a*b*c+d"
  patternStorage.setAssignPattern("x", " a 2 + ", 4);          // "a+2"
  patternStorage.setAssignPattern("x", " a b c * + ", 5);      // "a+b*c"

  SECTION("setAssignPattern and getAllStmtUsingVar") {
    std::unordered_set<std::pair<std::string, std::string>> actual =
        convertStringVectorToUnorderedSet(
            patternStorage.getAllAssignStatements());
    REQUIRE(actual ==
            std::unordered_set<std::pair<std::string, std::string>>{
                {"1", "x"}, {"2", "y"}, {"3", "z"}, {"4", "x"}, {"5", "x"}});
  }

  SECTION("getAllStatementsWithVariable") {
    REQUIRE(patternStorage.getAllAssignStatementsWithVariable("x") ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "x"}, {"4", "x"}, {"5", "x"}});
    REQUIRE(patternStorage.getAllAssignStatementsWithVariable("y") ==
            std::vector<std::pair<std::string, std::string>>{{"2", "y"}});
    REQUIRE(patternStorage.getAllAssignStatementsWithVariable("z") ==
            std::vector<std::pair<std::string, std::string>>{{"3", "y"}});
    REQUIRE(patternStorage.getAllAssignStatementsWithVariable("w").empty());
  }

  SECTION("getExactAssignPattern") {
    std::unordered_set<std::string> actual1 = convertStringVectorToUnorderedSet(
        patternStorage.getExactAssignPattern("x", " a b c * + ", false));
    REQUIRE(actual1 == std::unordered_set<std::string>{"1", "5"});
    std::unordered_set<std::string> actual2 = convertStringVectorToUnorderedSet(
        patternStorage.getExactAssignPattern("x", " a b c * + ", true));
    REQUIRE(patternStorage.getExactAssignPattern("x", "b", false).empty());
    std::unordered_set<std::string> actual3 = convertStringVectorToUnorderedSet(
        patternStorage.getExactAssignPattern("y", " d e + f + ", false));
    REQUIRE(actual3 == std::unordered_set<std::string>{"2"});
    std::unordered_set<std::string> actual4 = convertStringVectorToUnorderedSet(
        patternStorage.getExactAssignPattern("z", " a b c * + ", false));
    REQUIRE(actual4.empty());
    std::unordered_set<std::string> actual5 = convertStringVectorToUnorderedSet(
        patternStorage.getExactAssignPattern("v", " a b c * + ", true));
    REQUIRE(actual5 == std::unordered_set<std::string>{"1", "5"});
    std::unordered_set<std::string> actual6 = convertStringVectorToUnorderedSet(
        patternStorage.getExactAssignPattern("_", "_", false));
    REQUIRE(actual6 ==
            std::unordered_set<std::string>{"1", "2", "3", "4", "5"});
    std::unordered_set<std::string> actual7 = convertStringVectorToUnorderedSet(
        patternStorage.getExactAssignPattern("x", "_", false));
    REQUIRE(actual7 == std::unordered_set<std::string>{"1", "4", "5"});
    std::unordered_set<std::string> actual8 = convertStringVectorToUnorderedSet(
        patternStorage.getExactAssignPattern("_", " a b c * + ", false));
    REQUIRE(actual8 == std::unordered_set<std::string>{"1", "5"});
  }

  SECTION("getPartialAssignPattern") {
  std:
    unordered_set<std::string> actual1 = convertStringVectorToUnorderedSet(
        patternStorage.getPartialAssignPattern("x", " a b c * + ", false));
    REQUIRE(actual1 == std::unordered_set<std::string>{"1", "5"});
    std::unordered_set<std::string> actual2 = convertStringVectorToUnorderedSet(
        patternStorage.getPartialAssignPattern("x", " 2 ", false));
    REQUIRE(actual2 == std::unordered_set<std::string>{"4"});
    std::unordered_set<std::string> actual3 = convertStringVectorToUnorderedSet(
        patternStorage.getPartialAssignPattern("x", " 3 ", false));
    REQUIRE(actual3.empty());
    std::unordered_set<std::string> actual4 = convertStringVectorToUnorderedSet(
        patternStorage.getPartialAssignPattern("y", " f ", false));
    REQUIRE(actual4 == std::unordered_set<std::string>{"2"});
    std::unordered_set<std::string> actual5 = convertStringVectorToUnorderedSet(
        patternStorage.getPartialAssignPattern("_", " a ", false));
    REQUIRE(actual5 == std::unordered_set<std::string>{"1", "3", "4", "5"});
    std::unordered_set<std::string> actual6 = convertStringVectorToUnorderedSet(
        patternStorage.getPartialAssignPattern("v", " a ", true));
    REQUIRE(actual6 == std::unordered_set<std::string>{"1", "3", "4", "5"});
    std::unordered_set<std::string> actual7 = convertStringVectorToUnorderedSet(
        patternStorage.getPartialAssignPattern("x", "_", false));
    REQUIRE(actual7 == std::unordered_set<std::string>{"1", "4", "5"});
    std::unordered_set<std::string> actual8 = convertStringVectorToUnorderedSet(
        patternStorage.getPartialAssignPattern("v", "_", true));
    REQUIRE(actual8 ==
            std::unordered_set<std::string>{"1", "2", "3", "4", "5"});
    std::unordered_set<std::string> actual9 = convertStringVectorToUnorderedSet(
        patternStorage.getPartialAssignPattern("_", "_", false));
    REQUIRE(actual9 ==
            std::unordered_set<std::string>{"1", "2", "3", "4", "5"});
  }
}
