#include <unordered_set>
#include <catch.hpp>

#include "pkb/storage/pattern_storage/PatternStorage.h"
#include "../../common/utils/HelperFunctions.h"

TEST_CASE("PatternStorage Tests") {
  PatternStorage patternStorage;

  patternStorage.setAssignPattern("x", " a b c * + ", 1);      // "a+b*c"
  patternStorage.setAssignPattern("y", " d e + f + ", 2);      // "d+e+f"
  patternStorage.setAssignPattern("z", " a b * c * d + ", 3);  // "a*b*c+d"
  patternStorage.setAssignPattern("x", " a 2 + ", 4);          // "a+2"
  patternStorage.setAssignPattern("x", " a b c * + ", 5);      // "a+b*c"

  SECTION("addAssignPattern and getAllStmtUsingVar") {
    std::vector<std::pair<std::string, std::string>> actual =
        patternStorage.getAllAssignStatements();
    REQUIRE(actual ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "x"}, {"2", "y"}, {"3", "z"}, {"4", "x"}, {"5", "x"}});
  }

  SECTION("getAllStatementsWithVariable") {
    REQUIRE(patternStorage.getAllAssignStatementsWithVariable("x") ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "x"}, {"4", "x"}, {"5", "x"}});
    REQUIRE(patternStorage.getAllAssignStatementsWithVariable("y") ==
            std::vector<std::pair<std::string, std::string>>{{"2", "y"}});
    REQUIRE(patternStorage.getAllAssignStatementsWithVariable("z") ==
            std::vector<std::pair<std::string, std::string>>{{"3", "z"}});
    REQUIRE(patternStorage.getAllAssignStatementsWithVariable("w").empty());
  }

  SECTION("getExactAssignPattern") {
    std::vector<std::pair<std::string, std::string>> actual1 =
        patternStorage.getExactAssignPattern("x", " a b c * + ");
    REQUIRE(actual1 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual2 =
        patternStorage.getExactAssignPattern("x", " a b c * + ");
    REQUIRE(patternStorage.getExactAssignPattern("x", "b").empty());
    std::vector<std::pair<std::string, std::string>> actual3 =
        patternStorage.getExactAssignPattern("y", " d e + f + ");
    REQUIRE(actual3 ==
            std::vector<std::pair<std::string, std::string>>{{"2", "y"}});
    std::vector<std::pair<std::string, std::string>> actual4 =
        patternStorage.getExactAssignPattern("z", " a b c * + ");
    REQUIRE(actual4.empty());
    std::vector<std::pair<std::string, std::string>> actual5 =
        patternStorage.getExactAssignPattern("_", " a b c * + ");
    REQUIRE(actual5 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual6 =
        patternStorage.getExactAssignPattern("_", "_");
    REQUIRE(actual6 ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "x"}, {"2", "y"}, {"3", "z"}, {"4", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual7 =
        patternStorage.getExactAssignPattern("x", "_");
    REQUIRE(actual7 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"4", "x"}, {"5", "x"}});
  }

  SECTION("getPartialAssignPattern") {
    std::vector<std::pair<std::string, std::string>> actual1 =
        patternStorage.getPartialAssignPattern("x", " a b c * + ");
    REQUIRE(actual1 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual2 =
        patternStorage.getPartialAssignPattern("x", " 2 ");
    REQUIRE(actual2 ==
            std::vector<std::pair<std::string, std::string>>{{"4", "x"}});
    std::vector<std::pair<std::string, std::string>> actual3 =
        patternStorage.getPartialAssignPattern("x", " 3 ");
    REQUIRE(actual3.empty());
    std::vector<std::pair<std::string, std::string>> actual4 =
        patternStorage.getPartialAssignPattern("y", " f ");
    REQUIRE(actual4 ==
            std::vector<std::pair<std::string, std::string>>{{"2", "y"}});
    std::vector<std::pair<std::string, std::string>> actual5 =
        patternStorage.getPartialAssignPattern("_", " a ");
    REQUIRE(actual5 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"3", "z"}, {"4", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual6 =
        patternStorage.getPartialAssignPattern("_", " a ");
    REQUIRE(actual6 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"3", "z"}, {"4", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual7 =
        patternStorage.getPartialAssignPattern("x", "_");
    REQUIRE(actual7 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"4", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual8 =
        patternStorage.getPartialAssignPattern("_", "_");
    REQUIRE(actual8 ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "x"}, {"2", "y"}, {"3", "z"}, {"4", "x"}, {"5", "x"}});
  }
}

TEST_CASE("PatternStorage") {
  PatternStorage patternStorage;

  SECTION("addWhilePattern") {
    patternStorage.setWhilePattern(6, "x");
    patternStorage.setWhilePattern(6, "y");
    patternStorage.setWhilePattern(7, "y");
    patternStorage.setWhilePattern(8, "x");
    patternStorage.setWhilePattern(8, "z");
    patternStorage.setWhilePattern(9, "x");

    REQUIRE(patternStorage.getWhilePattern("x") ==
            std::vector<std::pair<std::string, std::string>>{
                {"6", "x"}, {"8", "x"}, {"9", "x"}});

    REQUIRE(patternStorage.getWhilePattern("y") ==
            std::vector<std::pair<std::string, std::string>>{{"6", "y"},
                                                             {"7", "y"}});

    REQUIRE(patternStorage.getWhilePattern("z") ==
            std::vector<std::pair<std::string, std::string>>{{"8", "z"}});

    REQUIRE(patternStorage.getWhilePattern("_") ==
            std::vector<std::pair<std::string, std::string>>{{"6", "x"},
                                                             {"6", "y"},
                                                             {"7", "y"},
                                                             {"8", "x"},
                                                             {"8", "z"},
                                                             {"9", "x"}});
  }

  SECTION("addIfPattern") {
    patternStorage.setIfPattern(6, "a");
    patternStorage.setIfPattern(7, "b");
    patternStorage.setIfPattern(8, "c");
    patternStorage.setIfPattern(9, "a");
    patternStorage.setIfPattern(10, "b");
    patternStorage.setIfPattern(11, "d");

    REQUIRE(patternStorage.getIfPattern("a") ==
            std::vector<std::pair<std::string, std::string>>{{"6", "a"},
                                                             {"9", "a"}});

    REQUIRE(patternStorage.getIfPattern("b") ==
            std::vector<std::pair<std::string, std::string>>{{"7", "b"},
                                                             {"10", "b"}});

    REQUIRE(patternStorage.getIfPattern("c") ==
            std::vector<std::pair<std::string, std::string>>{{"8", "c"}});

    REQUIRE(patternStorage.getIfPattern("_") ==
            std::vector<std::pair<std::string, std::string>>{{"6", "a"},
                                                             {"7", "b"},
                                                             {"8", "c"},
                                                             {"9", "a"},
                                                             {"10", "b"},
                                                             {"11", "d"}});
  }
}
