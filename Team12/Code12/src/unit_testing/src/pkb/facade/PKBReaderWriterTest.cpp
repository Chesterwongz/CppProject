#include <catch.hpp>
#include <unordered_set>

#include "../../common/utils/HelperFunctions.h"
#include "pkb/facade/PKBReader.h"
#include "pkb/facade/PKBWriter.h"

TEST_CASE("PKBReader Tests") {
  PKBStorage storage;
  PKBStore store;
  PKBWriter writer(storage);
  PKBReader reader(storage, store);

  writer.setVariable("x");
  writer.setVariable("y");
  writer.setVariable("z");

  writer.setStatement(1, StmtType::ASSIGN);
  writer.setStatement(2, StmtType::WHILE);
  writer.setStatement(3, StmtType::ASSIGN);
  writer.setStatement(4, StmtType::IF);
  writer.setStatement(5, StmtType::WHILE);
  writer.setStatement(6, StmtType::READ);

  writer.setFollowsRelationship(1, 2);
  writer.setFollowsRelationship(3, 4);
  writer.setFollowsRelationship(3, 5);
  writer.setFollowsRelationship(4, 5);

  writer.setParentRelationship(1, 2);
  writer.setParentRelationship(1, 3);
  writer.setParentRelationship(3, 4);
  writer.setParentRelationship(3, 5);
  writer.setParentStarRelationship(1, 2);
  writer.setParentStarRelationship(1, 3);
  writer.setParentStarRelationship(1, 4);
  writer.setParentStarRelationship(1, 5);
  writer.setParentStarRelationship(3, 4);
  writer.setParentStarRelationship(3, 5);

  writer.setModifiesRelationship("x", 1);
  writer.setModifiesRelationship("y", 2);
  writer.setModifiesRelationship("x", 3);
  writer.setModifiesRelationship("z", 4);
  writer.setModifiesRelationship("y", 5);
  writer.setModifiesRelationship("x", 6);

  writer.setUsesRelationship("x", 1);
  writer.setUsesRelationship("y", 1);
  writer.setUsesRelationship("x", 2);
  writer.setUsesRelationship("z", 3);
  writer.setUsesRelationship("x", 4);

  writer.setAssignPattern("x", " a b c * + ", 1);
  writer.setAssignPattern("y", " d e + f + ", 2);
  writer.setAssignPattern("z", " a b * c * d + ", 3);
  writer.setAssignPattern("x", " a 2 + ", 4);

  SECTION("getAllVarUsedByStmt") {
    REQUIRE(reader.getAllVariables() == std::set<std::string>{"x", "y", "z"});
  }

  SECTION("getAllConstants") {
    writer.setConstant("1");
    writer.setConstant("3");
    writer.setConstant("10");
    REQUIRE(reader.getAllConstants() == std::set<std::string>{"1", "3", "10"});
  }

  SECTION("getAllProcedures") {
    writer.setProcForStmt("proc1", 1);
    writer.setProcForStmt("proc2", 5);
    REQUIRE(reader.getAllProcedures() ==
            std::set<std::string>{"proc1", "proc2"});
  }

  SECTION("getStatement") {
    REQUIRE(reader.getStatement(StmtType::ASSIGN) ==
            std::set<std::string>{"1", "3"});
    REQUIRE(reader.getStatement(StmtType::WHILE) ==
            std::set<std::string>{"2", "5"});
    REQUIRE(reader.getStatement(StmtType::IF) == std::set<std::string>{"4"});
    REQUIRE(reader.getStatement(StmtType::READ) == std::set<std::string>{"6"});
    REQUIRE(reader.getStatement(StmtType::STMT) ==
            std::set<std::string>{"1", "2", "3", "4", "5", "6"});
  }

  SECTION("getFollowing") {
    REQUIRE(reader.getFollowing(1, StmtType::STMT) ==
            std::vector<std::string>{"2"});
    REQUIRE(reader.getFollowing(3, StmtType::STMT) ==
            std::vector<std::string>{"4"});
    REQUIRE(reader.getFollowing(4, StmtType::STMT) ==
            std::vector<std::string>{"5"});
    REQUIRE(reader.getFollowing(5, StmtType::STMT) ==
            std::vector<std::string>{});
  }

  SECTION("getFollowed") {
    REQUIRE(reader.getFollowed(2, StmtType::STMT) ==
            std::vector<std::string>{"1"});
    REQUIRE(reader.getFollowed(5, StmtType::STMT) ==
            std::vector<std::string>{"4"});
    REQUIRE(reader.getFollowed(4, StmtType::STMT) ==
            std::vector<std::string>{"3"});
    REQUIRE(reader.getFollowed(1, StmtType::STMT) ==
            std::vector<std::string>{});
  }

  SECTION("isFollows") {
    REQUIRE(reader.isFollows(1, 2) == true);
    REQUIRE(reader.isFollows(1, 4) == false);
    REQUIRE(reader.isFollows(3, 5) == false);
  }

  SECTION("getFollowsPairs") {
    REQUIRE(reader.getFollowsPairs(StmtType::STMT, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "2"}, {"3", "4"}, {"4", "5"}});
    REQUIRE(reader.getFollowsPairs(StmtType::ASSIGN, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{{"1", "2"},
                                                             {"3", "4"}});
    REQUIRE(reader.getFollowsPairs(StmtType::STMT, StmtType::WHILE) ==
            std::vector<std::pair<std::string, std::string>>{{"1", "2"},
                                                             {"4", "5"}});
    REQUIRE(reader.getFollowsPairs(StmtType::READ, StmtType::PRINT) ==
            std::vector<std::pair<std::string, std::string>>{});
  }

  SECTION("getAllFollowing") {
    REQUIRE(reader.getFollowsStar(1, StmtType::STMT) ==
            std::vector<std::string>{{"2"}});
    REQUIRE(reader.getFollowsStar(3, StmtType::STMT) ==
            std::vector<std::string>{{"4"}, {"5"}});
    REQUIRE(reader.getFollowsStar(3, StmtType::IF) ==
            std::vector<std::string>{{"4"}});
    REQUIRE(reader.getFollowsStar(3, StmtType::READ) ==
            std::vector<std::string>{});
    REQUIRE(reader.getFollowsStar(4, StmtType::STMT) ==
            std::vector<std::string>{{"5"}});
    REQUIRE(reader.getFollowsStar(5, StmtType::STMT) ==
            std::vector<std::string>{});
  }

  SECTION("getAllFollowed") {
    REQUIRE(reader.getFollowedStar(2, StmtType::STMT) ==
            std::vector<std::string>{{"1"}});
    REQUIRE(reader.getFollowedStar(5, StmtType::STMT) ==
            std::vector<std::string>{{"3"}, {"4"}});
    REQUIRE(reader.getFollowedStar(5, StmtType::ASSIGN) ==
            std::vector<std::string>{{"3"}});
    REQUIRE(reader.getFollowedStar(4, StmtType::STMT) ==
            std::vector<std::string>{{"3"}});
    REQUIRE(reader.getFollowedStar(4, StmtType::PRINT) ==
            std::vector<std::string>{});
    REQUIRE(reader.getFollowedStar(1, StmtType::STMT) ==
            std::vector<std::string>{});
  }

  SECTION("isFollowsStar") {
    REQUIRE(reader.isFollowsStar(3, 5) == true);
    REQUIRE(reader.isFollowsStar(1, 4) == false);
  }

  SECTION("getFollowsStarPairs") {
    REQUIRE(reader.getFollowsStarPairs(StmtType::STMT, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "2"}, {"3", "4"}, {"3", "5"}, {"4", "5"}});
    REQUIRE(reader.getFollowsStarPairs(StmtType::STMT, StmtType::WHILE) ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "2"}, {"3", "5"}, {"4", "5"}});
    REQUIRE(reader.getFollowsStarPairs(StmtType::ASSIGN, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "2"}, {"3", "4"}, {"3", "5"}});
    REQUIRE(reader.getFollowsStarPairs(StmtType::PRINT, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{});
  }

  SECTION("getImmediateChildren") {
    REQUIRE(reader.getImmediateChildrenOf(1, StmtType::STMT) ==
            std::vector<std::string>{"2", "3"});
    REQUIRE(reader.getImmediateChildrenOf(3, StmtType::STMT) ==
            std::vector<std::string>{"4", "5"});
    REQUIRE(reader.getImmediateChildrenOf(3, StmtType::IF) ==
            std::vector<std::string>{"4"});
    REQUIRE(reader.getImmediateChildrenOf(3, StmtType::READ) ==
            std::vector<std::string>{});
    REQUIRE(reader.getImmediateChildrenOf(4, StmtType::STMT) ==
            std::vector<std::string>{});
  }

  SECTION("getImmediateParent") {
    REQUIRE(reader.getImmediateParentOf(2, StmtType::STMT) ==
            std::vector<std::string>{"1"});
    REQUIRE(reader.getImmediateParentOf(3, StmtType::STMT) ==
            std::vector<std::string>{"1"});
    REQUIRE(reader.getImmediateParentOf(3, StmtType::ASSIGN) ==
            std::vector<std::string>{"1"});
    REQUIRE(reader.getImmediateParentOf(3, StmtType::READ) ==
            std::vector<std::string>{});
    REQUIRE(reader.getImmediateParentOf(3, StmtType::CALL) ==
            std::vector<std::string>{});
    REQUIRE(reader.getImmediateParentOf(4, StmtType::STMT) ==
            std::vector<std::string>{"3"});
    REQUIRE(reader.getImmediateParentOf(5, StmtType::STMT) ==
            std::vector<std::string>{"3"});
  }

  SECTION("isParent") {
    REQUIRE(reader.isParent(1, 3) == true);
    REQUIRE(reader.isParent(1, 4) == false);
    REQUIRE(reader.isParent(3, 4) == true);
  }

  SECTION("getParentChildPairs") {
    REQUIRE(reader.getParentChildPairs(StmtType::STMT, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "2"}, {"1", "3"}, {"3", "4"}, {"3", "5"}});
    REQUIRE(reader.getParentChildPairs(StmtType::READ, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{});
  }

  SECTION("getChildrenStar") {
    REQUIRE(reader.getChildrenStarOf(1, StmtType::STMT) ==
            std::vector<std::string>{"2", "3", "4", "5"});
    REQUIRE(reader.getChildrenStarOf(1, StmtType::WHILE) ==
            std::vector<std::string>{"2", "5"});
    REQUIRE(reader.getChildrenStarOf(1, StmtType::READ) ==
            std::vector<std::string>{});
    REQUIRE(reader.getChildrenStarOf(2, StmtType::STMT) ==
            std::vector<std::string>{});
    REQUIRE(reader.getChildrenStarOf(3, StmtType::STMT) ==
            std::vector<std::string>{"4", "5"});
    REQUIRE(reader.getChildrenStarOf(5, StmtType::STMT) ==
            std::vector<std::string>{});
  }

  SECTION("getParentStar") {
    REQUIRE(reader.getParentStarOf(1, StmtType::STMT) ==
            std::vector<std::string>{});
    REQUIRE(reader.getParentStarOf(2, StmtType::STMT) ==
            std::vector<std::string>{"1"});
    REQUIRE(reader.getParentStarOf(2, StmtType::ASSIGN) ==
            std::vector<std::string>{"1"});
    REQUIRE(reader.getParentStarOf(2, StmtType::READ) ==
            std::vector<std::string>{});
    REQUIRE(reader.getParentStarOf(4, StmtType::STMT) ==
            std::vector<std::string>{"1", "3"});
    REQUIRE(reader.getParentStarOf(4, StmtType::ASSIGN) ==
            std::vector<std::string>{"1", "3"});
    REQUIRE(reader.getParentStarOf(5, StmtType::PRINT) ==
            std::vector<std::string>{});
  }

  SECTION("isParentStar") {
    REQUIRE(reader.isParentStar(1, 3) == true);
    REQUIRE(reader.isParentStar(1, 5) == true);
    REQUIRE(reader.isParentStar(2, 3) == false);
  }

  SECTION("getParentChildStarPairs") {
    REQUIRE(reader.getParentChildStarPairs(StmtType::STMT, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{{"1", "2"},
                                                             {"1", "3"},
                                                             {"1", "4"},
                                                             {"1", "5"},
                                                             {"3", "4"},
                                                             {"3", "5"}});
    REQUIRE(reader.getParentChildStarPairs(StmtType::READ, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{});
    REQUIRE(reader.getParentChildStarPairs(StmtType::ASSIGN, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{{"1", "2"},
                                                             {"1", "3"},
                                                             {"1", "4"},
                                                             {"1", "5"},
                                                             {"3", "4"},
                                                             {"3", "5"}});
    REQUIRE(reader.getParentChildStarPairs(StmtType::ASSIGN, StmtType::WHILE) ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "2"}, {"1", "5"}, {"3", "5"}});
  }

  SECTION("getStatementsModifying") {
    REQUIRE(reader.getStatementsModifying("x", StmtType::STMT) ==
            std::vector<std::string>{"1", "3", "6"});
    REQUIRE(reader.getStatementsModifying("x", StmtType::ASSIGN) ==
            std::vector<std::string>{"1", "3"});
    REQUIRE(reader.getStatementsModifying("x", StmtType::READ) ==
            std::vector<std::string>{"6"});
    REQUIRE(reader.getStatementsModifying("x", StmtType::PRINT) ==
            std::vector<std::string>{});
    REQUIRE(reader.getStatementsModifying("y", StmtType::STMT) ==
            std::vector<std::string>{"2", "5"});
  }

  SECTION("getVariablesModifiedBy") {
    REQUIRE(reader.getVariablesModifiedBy(1, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{{"1", "x"}});
    REQUIRE(reader.getVariablesModifiedBy(2, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{{"2", "y"}});
    REQUIRE(reader.getVariablesModifiedBy(7, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{});
  }

  SECTION("getStatementsUsing") {
    REQUIRE(reader.getStatementsUsing("x", StmtType::STMT) ==
            std::vector<std::string>{"1", "2", "4"});
    REQUIRE(reader.getStatementsUsing("x", StmtType::ASSIGN) ==
            std::vector<std::string>{"1"});
    REQUIRE(reader.getStatementsUsing("x", StmtType::READ) ==
            std::vector<std::string>{});
    REQUIRE(reader.getStatementsUsing("y", StmtType::STMT) ==
            std::vector<std::string>{"1"});
    REQUIRE(reader.getStatementsUsing("a", StmtType::STMT) ==
            std::vector<std::string>{});
  }

  SECTION("getVariablesUsedBy") {
    REQUIRE(reader.getVariablesUsedBy(1, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{{"1", "x"},
                                                             {"1", "y"}});
    REQUIRE(reader.getVariablesUsedBy(1, StmtType::ASSIGN) ==
            std::vector<std::pair<std::string, std::string>>{{"1", "x"},
                                                             {"1", "y"}});
    REQUIRE(reader.getVariablesUsedBy(1, StmtType::PRINT) ==
            std::vector<std::pair<std::string, std::string>>{});
    REQUIRE(reader.getVariablesUsedBy(2, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{{"2", "x"}});
    REQUIRE(reader.getVariablesUsedBy(7, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{});
  }

  SECTION("getAllModifiedVariables") {
    REQUIRE(reader.getAllModifiedVariables(StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{{"1", "x"},
                                                             {"3", "x"},
                                                             {"6", "x"},
                                                             {"2", "y"},
                                                             {"5", "y"},
                                                             {"4", "z"}});
    REQUIRE(reader.getAllModifiedVariables(StmtType::ASSIGN) ==
            std::vector<std::pair<std::string, std::string>>{{"1", "x"},
                                                             {"3", "x"}});
    REQUIRE(reader.getAllModifiedVariables(StmtType::IF) ==
            std::vector<std::pair<std::string, std::string>>{{"4", "z"}});
    REQUIRE(reader.getAllModifiedVariables(StmtType::PRINT) ==
            std::vector<std::pair<std::string, std::string>>{});
  }

  SECTION("getUsesPairs") {
    REQUIRE(reader.getUsesPairs(StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "x"}, {"2", "x"}, {"4", "x"}, {"1", "y"}, {"3", "z"}});
    REQUIRE(reader.getUsesPairs(StmtType::ASSIGN) ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "x"}, {"1", "y"}, {"3", "z"}});
    REQUIRE(reader.getUsesPairs(StmtType::IF) ==
            std::vector<std::pair<std::string, std::string>>{{"4", "x"}});
    REQUIRE(reader.getUsesPairs(StmtType::PRINT).empty());
  }

  SECTION("getExactAssignPattern") {
    std::vector<std::pair<std::string, std::string>> resultVector1 =
        reader.getExactAssignPattern("x", " a b c * + ");
    std::vector<std::pair<std::string, std::string>> resultVector2 =
        reader.getExactAssignPattern("x", " b ");
    std::vector<std::pair<std::string, std::string>> resultVector3 =
        reader.getExactAssignPattern("y", " d e + f + ");
    std::vector<std::pair<std::string, std::string>> resultVector4 =
        reader.getExactAssignPattern("z", " a b c * + ");
    std::vector<std::pair<std::string, std::string>> resultVector5 =
        reader.getExactAssignPattern("_", " a b c * + ");
    std::vector<std::pair<std::string, std::string>> resultVector6 =
        reader.getExactAssignPattern("_", "_");
    std::vector<std::pair<std::string, std::string>> resultVector7 =
        reader.getExactAssignPattern("x", "_");
    REQUIRE(resultVector1 ==
            std::vector<std::pair<std::string, std::string>>{{"1", "x"}});
    REQUIRE(resultVector2.empty());
    REQUIRE(resultVector3 ==
            std::vector<std::pair<std::string, std::string>>{{"2", "y"}});
    REQUIRE(resultVector4.empty());
    REQUIRE(resultVector5 ==
            std::vector<std::pair<std::string, std::string>>{{"1", "x"}});
    REQUIRE(resultVector6 ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "x"}, {"2", "y"}, {"3", "z"}, {"4", "x"}});
    REQUIRE(resultVector7 == std::vector<std::pair<std::string, std::string>>{
                                 {"1", "x"}, {"4", "x"}});
  }

  SECTION("getPartialAssignPattern") {
    std::vector<std::pair<std::string, std::string>> resultVector1 =
        reader.getPartialAssignPattern("x", " a b c * + ");
    std::vector<std::pair<std::string, std::string>> resultVector2 =
        reader.getPartialAssignPattern("x", " 2 ");
    std::vector<std::pair<std::string, std::string>> resultVector3 =
        reader.getPartialAssignPattern("x", " 3 ");
    std::vector<std::pair<std::string, std::string>> resultVector4 =
        reader.getPartialAssignPattern("_", " a ");
    std::vector<std::pair<std::string, std::string>> resultVector5 =
        reader.getPartialAssignPattern("_", " a ");
    std::vector<std::pair<std::string, std::string>> resultVector6 =
        reader.getPartialAssignPattern("x", "_");
    std::vector<std::pair<std::string, std::string>> resultVector7 =
        reader.getPartialAssignPattern("_", "_");

    REQUIRE(resultVector1 ==
            std::vector<std::pair<std::string, std::string>>{{"1", "x"}});
    REQUIRE(resultVector2 ==
            std::vector<std::pair<std::string, std::string>>{{"4", "x"}});
    REQUIRE(resultVector3.empty());
    REQUIRE(resultVector4 == std::vector<std::pair<std::string, std::string>>{
                                 {"1", "x"}, {"3", "z"}, {"4", "x"}});
    REQUIRE(resultVector5 == std::vector<std::pair<std::string, std::string>>{
                                 {"1", "x"}, {"3", "z"}, {"4", "x"}});
    REQUIRE(resultVector6 == std::vector<std::pair<std::string, std::string>>{
                                 {"1", "x"}, {"4", "x"}});
    REQUIRE(resultVector7 ==
            std::vector<std::pair<std::string, std::string>>{
                {"1", "x"}, {"2", "y"}, {"3", "z"}, {"4", "x"}});
  }

  SECTION("Test whilePattern") {
    writer.setWhilePattern(6, "x");
    writer.setWhilePattern(6, "y");
    writer.setWhilePattern(7, "y");
    writer.setWhilePattern(8, "x");
    writer.setWhilePattern(8, "z");
    writer.setWhilePattern(9, "x");

    REQUIRE(reader.getWhilePattern("x") ==
            std::vector<std::pair<std::string, std::string>>{
                {"6", "x"}, {"8", "x"}, {"9", "x"}});

    REQUIRE(reader.getWhilePattern("y") ==
            std::vector<std::pair<std::string, std::string>>{{"6", "y"},
                                                             {"7", "y"}});

    REQUIRE(reader.getWhilePattern("z") ==
            std::vector<std::pair<std::string, std::string>>{{"8", "z"}});

    REQUIRE(reader.getWhilePattern("_") ==
            std::vector<std::pair<std::string, std::string>>{{"6", "x"},
                                                             {"6", "y"},
                                                             {"7", "y"},
                                                             {"8", "x"},
                                                             {"8", "z"},
                                                             {"9", "x"}});
  }

  SECTION("Test ifPattern") {
    writer.setIfPattern(6, "a");
    writer.setIfPattern(7, "b");
    writer.setIfPattern(8, "c");
    writer.setIfPattern(9, "a");
    writer.setIfPattern(10, "b");
    writer.setIfPattern(11, "d");

    REQUIRE(reader.getIfPattern("a") ==
            std::vector<std::pair<std::string, std::string>>{{"6", "a"},
                                                             {"9", "a"}});

    REQUIRE(reader.getIfPattern("b") ==
            std::vector<std::pair<std::string, std::string>>{{"7", "b"},
                                                             {"10", "b"}});

    REQUIRE(reader.getIfPattern("c") ==
            std::vector<std::pair<std::string, std::string>>{{"8", "c"}});

    REQUIRE(reader.getIfPattern("_") ==
            std::vector<std::pair<std::string, std::string>>{{"6", "a"},
                                                             {"7", "b"},
                                                             {"8", "c"},
                                                             {"9", "a"},
                                                             {"10", "b"},
                                                             {"11", "d"}});
  }
}
