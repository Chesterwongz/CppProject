#include <unordered_set>
#include <catch.hpp>

#include "../../common/utils/HelperFunctions.h"
#include "pkb/facade/PKBReader.h"
#include "pkb/facade/PKBWriter.h"

TEST_CASE("PKBReader Tests") {
  PKBStorage storage;
  PKBStore store;
  PKBWriter writer(storage, store);
  PKBReader reader(storage, store);

  writer.addVariable("x");
  writer.addVariable("y");
  writer.addVariable("z");

  writer.addStmt(1, StmtType::ASSIGN);
  writer.addStmt(2, StmtType::WHILE);
  writer.addStmt(3, StmtType::ASSIGN);
  writer.addStmt(4, StmtType::IF);
  writer.addStmt(5, StmtType::WHILE);
  writer.addStmt(6, StmtType::READ);

  writer.addFollows(1, 2);
  writer.addFollows(3, 4);
  writer.addFollows(3, 5);
  writer.addFollows(4, 5);

  writer.addParent(1, 2);
  writer.addParent(1, 3);
  writer.addParent(3, 4);
  writer.addParent(3, 5);
  writer.setParentStarRelationship(1, 2);
  writer.setParentStarRelationship(1, 3);
  writer.setParentStarRelationship(1, 4);
  writer.setParentStarRelationship(1, 5);
  writer.setParentStarRelationship(3, 4);
  writer.setParentStarRelationship(3, 5);

  writer.addModifies("x", 1);
  writer.addModifies("y", 2);
  writer.addModifies("x", 3);
  writer.addModifies("z", 4);
  writer.addModifies("y", 5);
  writer.addModifies("x", 6);

  writer.addUses("x", 1);
  writer.addUses("y", 1);
  writer.addUses("x", 2);
  writer.addUses("z", 3);
  writer.addUses("x", 4);

  writer.addAssignPattern("x", " a b c * + ", 1);
  writer.addAssignPattern("y", " d e + f + ", 2);
  writer.addAssignPattern("z", " a b * c * d + ", 3);
  writer.addAssignPattern("x", " a 2 + ", 4);

  SECTION("getAllVarUsedByStmt") {
    REQUIRE(reader.getAllVariables() == std::set<std::string> {"x", "y", "z"});
  }

  SECTION("getAllConstants") {
    writer.addConstant("1");
    writer.addConstant("3");
    writer.addConstant("10");
    REQUIRE(reader.getAllConstants() == std::set<std::string> {"1", "3", "10"});
  }

  SECTION("getAllProcedures") {
    writer.addProcForStmt("proc1", 1);
    writer.addProcForStmt("proc2", 5);
    REQUIRE(reader.getAllProcedures() ==
            std::set<std::string> {"proc1", "proc2"});
  }

  SECTION("getStatement") {
    REQUIRE(reader.getStatement(StmtType::ASSIGN) ==
            std::set<std::string> {"1", "3"});
    REQUIRE(reader.getStatement(StmtType::WHILE) ==
            std::set<std::string> {"2", "5"});
    REQUIRE(reader.getStatement(StmtType::IF) == std::set<std::string> {"4"});
    REQUIRE(reader.getStatement(StmtType::READ) == std::set<std::string> {"6"});
    REQUIRE(reader.getStatement(StmtType::STMT) ==
            std::set<std::string> {"1", "2", "3", "4", "5", "6"});
  }

  SECTION("getFollowing") {
    REQUIRE(reader.getFollowing(1, StmtType::STMT) ==
            std::vector<std::string> {"2"});
    REQUIRE(reader.getFollowing(3, StmtType::STMT) ==
            std::vector<std::string> {"4"});
    REQUIRE(reader.getFollowing(4, StmtType::STMT) ==
            std::vector<std::string> {"5"});
    REQUIRE(reader.getFollowing(5, StmtType::STMT) ==
            std::vector<std::string> {"-1"});
  }

  SECTION("getFollowed") {
    REQUIRE(reader.getFollowed(2, StmtType::STMT) ==
            std::vector<std::string> {"1"});
    REQUIRE(reader.getFollowed(5, StmtType::STMT) ==
            std::vector<std::string> {"4"});
    REQUIRE(reader.getFollowed(4, StmtType::STMT) ==
            std::vector<std::string> {"3"});
    REQUIRE(reader.getFollowed(1, StmtType::STMT) ==
            std::vector<std::string> {"-1"});
  }

  SECTION("isFollows") {
    REQUIRE(reader.isFollows(1, 2) == true);
    REQUIRE(reader.isFollows(1, 4) == false);
    REQUIRE(reader.isFollows(3, 5) == false);
  }

  SECTION("getFollowsPairs") {
    REQUIRE(reader.getFollowsPairs(StmtType::STMT, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>> {
                {"1", "2"}, {"3", "4"}, {"4", "5"}});
    REQUIRE(reader.getFollowsPairs(StmtType::ASSIGN, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>> {{"1", "2"},
                                                              {"3", "4"}});
    REQUIRE(reader.getFollowsPairs(StmtType::STMT, StmtType::WHILE) ==
            std::vector<std::pair<std::string, std::string>> {{"1", "2"},
                                                              {"4", "5"}});
    REQUIRE(reader.getFollowsPairs(StmtType::READ, StmtType::PRINT).empty());
  }

  SECTION("getAllFollowing") {
    REQUIRE(reader.getFollowsStar(1, StmtType::STMT) ==
            std::vector<std::string> {{"2"}});
    REQUIRE(reader.getFollowsStar(3, StmtType::STMT) ==
            std::vector<std::string> {"4", "5"});
    REQUIRE(reader.getFollowsStar(3, StmtType::IF) ==
            std::vector<std::string> {"4"});
    REQUIRE(reader.getFollowsStar(3, StmtType::READ).empty());
    REQUIRE(reader.getFollowsStar(4, StmtType::STMT) ==
            std::vector<std::string> {"5"});
    REQUIRE(reader.getFollowsStar(5, StmtType::STMT).empty());
  }

  SECTION("getAllFollowed") {
    REQUIRE(reader.getFollowedStar(2, StmtType::STMT) ==
            std::vector<std::string> {{"1"}});
    REQUIRE(reader.getFollowedStar(5, StmtType::STMT) ==
            std::vector<std::string> {{"3"}, {"4"}});
    REQUIRE(reader.getFollowedStar(5, StmtType::ASSIGN) ==
            std::vector<std::string> {{"3"}});
    REQUIRE(reader.getFollowedStar(4, StmtType::STMT) ==
            std::vector<std::string> {"3"});
    REQUIRE(reader.getFollowedStar(4, StmtType::PRINT).empty());
    REQUIRE(reader.getFollowedStar(1, StmtType::STMT).empty());
  }

  SECTION("isFollowsStar") {
    REQUIRE(reader.isFollowsStar(3, 5) == true);
    REQUIRE(reader.isFollowsStar(1, 4) == false);
  }

  SECTION("getFollowsStarPairs") {
    REQUIRE(reader.getFollowsStarPairs(StmtType::STMT, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>> {
                {"1", "2"}, {"3", "4"}, {"3", "5"}, {"4", "5"}});
    REQUIRE(reader.getFollowsStarPairs(StmtType::STMT, StmtType::WHILE) ==
            std::vector<std::pair<std::string, std::string>> {
                {"1", "2"}, {"3", "5"}, {"4", "5"}});
    REQUIRE(reader.getFollowsStarPairs(StmtType::ASSIGN, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>> {
                {"1", "2"}, {"3", "4"}, {"3", "5"}});
    REQUIRE(
        reader.getFollowsStarPairs(StmtType::PRINT, StmtType::STMT).empty());
  }

  SECTION("getImmediateChildren") {
    REQUIRE(reader.getImmediateChildrenOf(1, StmtType::STMT) ==
            std::vector<std::string> {"2", "3"});
    REQUIRE(reader.getImmediateChildrenOf(3, StmtType::STMT) ==
            std::vector<std::string> {"4", "5"});
    REQUIRE(reader.getImmediateChildrenOf(3, StmtType::IF) ==
            std::vector<std::string> {"4"});
    REQUIRE(reader.getImmediateChildrenOf(3, StmtType::READ).empty());
    REQUIRE(reader.getImmediateChildrenOf(4, StmtType::STMT).empty());
    REQUIRE(reader.getImmediateChildrenOf(3, StmtType::READ).empty());
    REQUIRE(reader.getImmediateChildrenOf(4, StmtType::STMT).empty());
  }

  SECTION("getImmediateParent") {
    REQUIRE(reader.getImmediateParentOf(2, StmtType::STMT) ==
            std::vector<std::string> {"1"});
    REQUIRE(reader.getImmediateParentOf(3, StmtType::STMT) ==
            std::vector<std::string> {"1"});
    REQUIRE(reader.getImmediateParentOf(3, StmtType::ASSIGN) ==
            std::vector<std::string> {"1"});
    REQUIRE(reader.getImmediateParentOf(3, StmtType::READ).empty());
    REQUIRE(reader.getImmediateParentOf(3, StmtType::CALL).empty());
    REQUIRE(reader.getImmediateParentOf(4, StmtType::STMT) ==
            std::vector<std::string> {"3"});
    REQUIRE(reader.getImmediateParentOf(5, StmtType::STMT) ==
            std::vector<std::string> {"3"});
  }

  SECTION("isParent") {
    REQUIRE(reader.isParent(1, 3) == true);
    REQUIRE(reader.isParent(1, 4) == false);
    REQUIRE(reader.isParent(3, 4) == true);
  }

  SECTION("getParentChildPairs") {
    REQUIRE(reader.getParentChildPairs(StmtType::STMT, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>> {
                {"1", "2"}, {"1", "3"}, {"3", "4"}, {"3", "5"}});
    REQUIRE(reader.getParentChildPairs(StmtType::READ, StmtType::STMT).empty());
  }

  SECTION("getChildrenStar") {
    REQUIRE(reader.getChildrenStarOf(1, StmtType::STMT) ==
            std::vector<std::string> {"2", "3", "4", "5"});
    REQUIRE(reader.getChildrenStarOf(1, StmtType::WHILE) ==
            std::vector<std::string> {"2", "5"});
    REQUIRE(reader.getChildrenStarOf(1, StmtType::READ).empty());
    REQUIRE(reader.getChildrenStarOf(2, StmtType::STMT).empty());
    REQUIRE(reader.getChildrenStarOf(3, StmtType::STMT) ==
            std::vector<std::string> {"4", "5"});
    REQUIRE(reader.getChildrenStarOf(5, StmtType::STMT).empty());
  }

  SECTION("getParentStar") {
    REQUIRE(reader.getParentStarOf(1, StmtType::STMT).empty());
    REQUIRE(reader.getParentStarOf(2, StmtType::STMT) ==
            std::vector<std::string> {"1"});
    REQUIRE(reader.getParentStarOf(2, StmtType::ASSIGN) ==
            std::vector<std::string> {"1"});
    REQUIRE(reader.getParentStarOf(2, StmtType::READ).empty());
    REQUIRE(reader.getParentStarOf(4, StmtType::STMT) ==
            std::vector<std::string> {"1", "3"});
    REQUIRE(reader.getParentStarOf(4, StmtType::ASSIGN) ==
            std::vector<std::string> {"1", "3"});
    REQUIRE(reader.getParentStarOf(5, StmtType::PRINT).empty());
  }

  SECTION("isParentStar") {
    REQUIRE(reader.isParentStar(1, 3) == true);
    REQUIRE(reader.isParentStar(1, 5) == true);
    REQUIRE(reader.isParentStar(2, 3) == false);
  }

  SECTION("getParentChildStarPairs") {
    REQUIRE(reader.getParentChildStarPairs(StmtType::STMT, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>> {{"1", "2"},
                                                              {"1", "3"},
                                                              {"1", "4"},
                                                              {"1", "5"},
                                                              {"3", "4"},
                                                              {"3", "5"}});
    REQUIRE(
        reader.getParentChildStarPairs(StmtType::READ, StmtType::STMT).empty());
    REQUIRE(reader.getParentChildStarPairs(StmtType::ASSIGN, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>> {{"1", "2"},
                                                              {"1", "3"},
                                                              {"1", "4"},
                                                              {"1", "5"},
                                                              {"3", "4"},
                                                              {"3", "5"}});
    REQUIRE(reader.getParentChildStarPairs(StmtType::ASSIGN, StmtType::WHILE) ==
            std::vector<std::pair<std::string, std::string>> {
                {"1", "2"}, {"1", "5"}, {"3", "5"}});
  }

  SECTION("getStatementsModifying") {
    REQUIRE(reader.getStatementsModifying("x", StmtType::STMT) ==
            std::vector<std::string> {"1", "3", "6"});
    REQUIRE(reader.getStatementsModifying("x", StmtType::ASSIGN) ==
            std::vector<std::string> {"1", "3"});
    REQUIRE(reader.getStatementsModifying("x", StmtType::READ) ==
            std::vector<std::string> {"6"});
    REQUIRE(reader.getStatementsModifying("x", StmtType::PRINT).empty());
    REQUIRE(reader.getStatementsModifying("y", StmtType::STMT) ==
            std::vector<std::string> {"2", "5"});
  }

  SECTION("getVariablesModifiedBy") {
    REQUIRE(reader.getVariablesModifiedBy(1, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>> {{"1", "x"}});
    REQUIRE(reader.getVariablesModifiedBy(2, StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>> {{"2", "y"}});
    REQUIRE(reader.getVariablesModifiedBy(7, StmtType::STMT).empty());
  }

  SECTION("getStatementsUsing") {
    REQUIRE(reader.getStatementsUsing("x", StmtType::STMT) ==
            std::vector<std::string> {"1", "2", "4"});
    REQUIRE(reader.getStatementsUsing("x", StmtType::ASSIGN) ==
            std::vector<std::string> {"1"});
    REQUIRE(reader.getStatementsUsing("x", StmtType::READ).empty());
    REQUIRE(reader.getStatementsUsing("y", StmtType::STMT) ==
            std::vector<std::string> {"1"});
    REQUIRE(reader.getStatementsUsing("a", StmtType::STMT).empty());
  }

  SECTION("getVariablesUsedBy") {
    REQUIRE(reader.getVariablesUsedBy(1) ==
            std::vector<std::string> {"x", "y"});
    REQUIRE(reader.getVariablesUsedBy(2) == std::vector<std::string> {"x"});
    REQUIRE(reader.getVariablesUsedBy(7).empty());
    REQUIRE(reader.getVariablesUsedBy(1) ==
            std::vector<std::string> {"x", "y"});
    REQUIRE(reader.getVariablesUsedBy(1) ==
            std::vector<std::string> {"x", "y"});
    REQUIRE(reader.getVariablesUsedBy(1).empty());
    REQUIRE(reader.getVariablesUsedBy(2) == std::vector<std::string> {"x"});
    REQUIRE(reader.getVariablesUsedBy(7).empty());
  }

  SECTION("getAllModifiedVariables") {
    REQUIRE(reader.getAllModifiedVariables(StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>> {{"1", "x"},
                                                              {"3", "x"},
                                                              {"6", "x"},
                                                              {"2", "y"},
                                                              {"5", "y"},
                                                              {"4", "z"}});
    REQUIRE(reader.getAllModifiedVariables(StmtType::ASSIGN) ==
            std::vector<std::pair<std::string, std::string>> {{"1", "x"},
                                                              {"3", "x"}});
    REQUIRE(reader.getAllModifiedVariables(StmtType::IF) ==
            std::vector<std::pair<std::string, std::string>> {{"4", "z"}});
    REQUIRE(reader.getAllModifiedVariables(StmtType::PRINT).empty());
  }

  SECTION("getUsesPairs") {
    REQUIRE(reader.getUsesPairs(StmtType::STMT) ==
            std::vector<std::pair<std::string, std::string>> {
                {"1", "x"}, {"2", "x"}, {"4", "x"}, {"1", "y"}, {"3", "z"}});
    REQUIRE(reader.getUsesPairs(StmtType::ASSIGN) ==
            std::vector<std::pair<std::string, std::string>> {
                {"1", "x"}, {"1", "y"}, {"3", "z"}});
    REQUIRE(reader.getUsesPairs(StmtType::IF) ==
            std::vector<std::pair<std::string, std::string>> {{"4", "x"}});
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
    REQUIRE(StrStrPairSet {resultVector1.begin(), resultVector1.end()} ==
            StrStrPairSet {{"1", "x"}});
    REQUIRE(resultVector2.empty());
    REQUIRE(StrStrPairSet {resultVector3.begin(), resultVector3.end()} ==
            StrStrPairSet {{"2", "y"}});
    REQUIRE(resultVector4.empty());
    REQUIRE(StrStrPairSet {resultVector5.begin(), resultVector5.end()} ==
            StrStrPairSet {{"1", "x"}});
    REQUIRE(StrStrPairSet {resultVector6.begin(), resultVector6.end()} ==
            StrStrPairSet {{"1", "x"}, {"2", "y"}, {"3", "z"}, {"4", "x"}});
    REQUIRE(StrStrPairSet {resultVector7.begin(), resultVector7.end()} ==
            StrStrPairSet {{"1", "x"}, {"4", "x"}});
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

    REQUIRE(StrStrPairSet {resultVector1.begin(), resultVector1.end()} ==
            StrStrPairSet {{"1", "x"}});
    REQUIRE(StrStrPairSet {resultVector2.begin(), resultVector2.end()} ==
            StrStrPairSet {{"4", "x"}});
    REQUIRE(resultVector3.empty());
    REQUIRE(StrStrPairSet {resultVector4.begin(), resultVector4.end()} ==
            StrStrPairSet {{"1", "x"}, {"3", "z"}, {"4", "x"}});
    REQUIRE(StrStrPairSet {resultVector5.begin(), resultVector5.end()} ==
            StrStrPairSet {{"1", "x"}, {"3", "z"}, {"4", "x"}});
    REQUIRE(StrStrPairSet {resultVector6.begin(), resultVector6.end()} ==
            StrStrPairSet {{"1", "x"}, {"4", "x"}});
    REQUIRE(StrStrPairSet {resultVector7.begin(), resultVector7.end()} ==
            StrStrPairSet {{"1", "x"}, {"2", "y"}, {"3", "z"}, {"4", "x"}});
  }

  SECTION("Test whilePattern") {
    writer.addWhilePattern(6, "x");
    writer.addWhilePattern(6, "y");
    writer.addWhilePattern(7, "y");
    writer.addWhilePattern(8, "x");
    writer.addWhilePattern(8, "z");
    writer.addWhilePattern(9, "x");

    std::vector<std::pair<std::string, std::string>> resultVec1 =
        reader.getWhilePattern("x");
    std::vector<std::pair<std::string, std::string>> resultVec2 =
        reader.getWhilePattern("y");
    std::vector<std::pair<std::string, std::string>> resultVec3 =
        reader.getWhilePattern("z");
    std::vector<std::pair<std::string, std::string>> resultVec4 =
        reader.getWhilePattern("_");

    REQUIRE(StrStrPairSet {resultVec1.begin(), resultVec1.end()} ==
            StrStrPairSet {{"6", "x"}, {"8", "x"}, {"9", "x"}});

    REQUIRE(StrStrPairSet {resultVec2.begin(), resultVec2.end()} ==
            StrStrPairSet {{"6", "y"}, {"7", "y"}});

    REQUIRE(StrStrPairSet {resultVec3.begin(), resultVec3.end()} ==
            StrStrPairSet {{"8", "z"}});

    REQUIRE(StrStrPairSet {resultVec4.begin(), resultVec4.end()} ==
            StrStrPairSet {{"6", "x"},
                           {"6", "y"},
                           {"7", "y"},
                           {"8", "x"},
                           {"8", "z"},
                           {"9", "x"}});
  }

  SECTION("Test ifPattern") {
    writer.addIfPattern(6, "a");
    writer.addIfPattern(7, "b");
    writer.addIfPattern(8, "c");
    writer.addIfPattern(9, "a");
    writer.addIfPattern(10, "b");
    writer.addIfPattern(11, "d");

    std::vector<std::pair<std::string, std::string>> resultVec1 =
        reader.getIfPattern("a");
    std::vector<std::pair<std::string, std::string>> resultVec2 =
        reader.getIfPattern("b");
    std::vector<std::pair<std::string, std::string>> resultVec3 =
        reader.getIfPattern("c");
    std::vector<std::pair<std::string, std::string>> resultVec4 =
        reader.getIfPattern("_");

    REQUIRE(StrStrPairSet {resultVec1.begin(), resultVec1.end()} ==
            StrStrPairSet {{"6", "a"}, {"9", "a"}});

    REQUIRE(StrStrPairSet {resultVec2.begin(), resultVec2.end()} ==
            StrStrPairSet {{"7", "b"}, {"10", "b"}});

    REQUIRE(StrStrPairSet {resultVec3.begin(), resultVec3.end()} ==
            StrStrPairSet {{"8", "c"}});

    REQUIRE(StrStrPairSet {resultVec4.begin(), resultVec4.end()} ==
            StrStrPairSet {{"6", "a"},
                           {"7", "b"},
                           {"8", "c"},
                           {"9", "a"},
                           {"10", "b"},
                           {"11", "d"}});
  }
}
