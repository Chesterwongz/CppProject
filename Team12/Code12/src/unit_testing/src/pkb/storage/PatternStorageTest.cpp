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
            std::vector<std::pair<std::string, std::string>>{{"3", "y"}});
    REQUIRE(patternStorage.getAllAssignStatementsWithVariable("w").empty());
  }

  SECTION("getExactAssignPattern") {
    std::vector<std::pair<std::string, std::string>> actual1 =
        patternStorage.getExactAssignPattern("x", " a b c * + ", false);
    REQUIRE(actual1 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual2 =
        patternStorage.getExactAssignPattern("x", " a b c * + ", true);
    REQUIRE(patternStorage.getExactAssignPattern("x", "b", false).empty());
    std::vector<std::pair<std::string, std::string>> actual3 =
        patternStorage.getExactAssignPattern("y", " d e + f + ", false);
    REQUIRE(actual3 ==
            std::vector<std::pair<std::string, std::string>>{{"2", "y"}});
    std::vector<std::pair<std::string, std::string>> actual4 =
        patternStorage.getExactAssignPattern("z", " a b c * + ", false);
    REQUIRE(actual4.empty());
    std::vector<std::pair<std::string, std::string>> actual5 =
        patternStorage.getExactAssignPattern("v", " a b c * + ", true);
    REQUIRE(actual5 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual6 =
        patternStorage.getExactAssignPattern("_", "_", false);
    REQUIRE(actual6 ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "x"}, {"2", "y"}, {"3", "z"}, {"4", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual7 =
        patternStorage.getExactAssignPattern("x", "_", false);
    REQUIRE(actual7 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"4", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual8 =
        patternStorage.getExactAssignPattern("_", " a b c * + ", false);
    REQUIRE(actual8 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"5", "x"}});
  }

  SECTION("getPartialAssignPattern") {
    std::vector<std::pair<std::string, std::string>> actual1 =
        patternStorage.getPartialAssignPattern("x", " a b c * + ", false);
    REQUIRE(actual1 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual2 =
        patternStorage.getPartialAssignPattern("x", " 2 ", false);
    REQUIRE(actual2 ==
            std::vector<std::pair<std::string, std::string>>{{"4", "x"}});
    std::vector<std::pair<std::string, std::string>> actual3 =
        patternStorage.getPartialAssignPattern("x", " 3 ", false);
    REQUIRE(actual3.empty());
    std::vector<std::pair<std::string, std::string>> actual4 =
        patternStorage.getPartialAssignPattern("y", " f ", false);
    REQUIRE(actual4 ==
            std::vector<std::pair<std::string, std::string>>{{"2", "y"}});
    std::vector<std::pair<std::string, std::string>> actual5 =
        patternStorage.getPartialAssignPattern("_", " a ", false);
    REQUIRE(actual5 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"3", "z"}, {"4", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual6 =
        patternStorage.getPartialAssignPattern("v", " a ", true);
    REQUIRE(actual6 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"3", "z"}, {"4", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual7 =
        patternStorage.getPartialAssignPattern("x", "_", false);
    REQUIRE(actual7 == std::vector<std::pair<std::string, std::string>>{
                           {"1", "x"}, {"4", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual8 =
        patternStorage.getPartialAssignPattern("v", "_", true);
    REQUIRE(actual8 ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "x"}, {"2", "y"}, {"3", "z"}, {"4", "x"}, {"5", "x"}});
    std::vector<std::pair<std::string, std::string>> actual9 =
        patternStorage.getPartialAssignPattern("_", "_", false);
    REQUIRE(actual9 ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "x"}, {"2", "y"}, {"3", "z"}, {"4", "x"}, {"5", "x"}});
  }
}
