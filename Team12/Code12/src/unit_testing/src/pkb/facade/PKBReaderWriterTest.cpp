#include <catch.hpp>

#include "../../common/utils/HelperFunctions.h"
#include "pkb/facade/PKBReader.h"
#include "pkb/facade/PKBWriter.h"

TEST_CASE("PKBReader Tests") {
  PKBStorage storage;
  PKBStore store;
  PKBWriter writer(storage, store);
  PKBReader reader(storage, store);

  writer.addVar("x");
  writer.addVar("y");
  writer.addVar("z");

  writer.addStmt(1, StmtType::ASSIGN);
  writer.addStmt(2, StmtType::WHILE);
  writer.addStmt(3, StmtType::ASSIGN);
  writer.addStmt(4, StmtType::IF);
  writer.addStmt(5, StmtType::WHILE);
  writer.addStmt(6, StmtType::READ);

  writer.addFollows(1, 2);
  writer.addFollows(3, 4);
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
    REQUIRE(compareVectorContents(reader.getAllVariables(), {"x", "y", "z"}));
  }

  SECTION("getAllConstants") {
    writer.addConst("1");
    writer.addConst("3");
    writer.addConst("10");
    REQUIRE(compareVectorContents(reader.getAllConstants(), {"1", "3", "10"}));
  }

  SECTION("getAllProcedures") {
    writer.addProc("proc1");
    writer.addProc("proc2");
    REQUIRE(
        compareVectorContents(reader.getAllProcedures(), {"proc1", "proc2"}));
  }

  SECTION("getAllStmtsOf") {
    REQUIRE(compareVectorContents(reader.getAllStmtsOf(StmtType::ASSIGN),
                                  {"1", "3"}));
    REQUIRE(compareVectorContents(reader.getAllStmtsOf(StmtType::WHILE),
                                  {"2", "5"}));
    REQUIRE(compareVectorContents(reader.getAllStmtsOf(StmtType::IF), {"4"}));
    REQUIRE(compareVectorContents(reader.getAllStmtsOf(StmtType::READ), {"6"}));
    REQUIRE(compareVectorContents(reader.getAllStmtsOf(StmtType::STMT),
                                  {"1", "2", "3", "4", "5", "6"}));
  }

  SECTION("getFollowing") {
    REQUIRE(
        compareVectorContents(reader.getFollowing(1, StmtType::STMT), {"2"}));
    REQUIRE(
        compareVectorContents(reader.getFollowing(3, StmtType::STMT), {"4"}));
    REQUIRE(
        compareVectorContents(reader.getFollowing(4, StmtType::STMT), {"5"}));
    REQUIRE(reader.getFollowing(5, StmtType::STMT).empty());
  }

  SECTION("getFollowed") {
    REQUIRE(
        compareVectorContents(reader.getFollowed(2, StmtType::STMT), {"1"}));
    REQUIRE(
        compareVectorContents(reader.getFollowed(5, StmtType::STMT), {"4"}));
    REQUIRE(
        compareVectorContents(reader.getFollowed(4, StmtType::STMT), {"3"}));
    REQUIRE(reader.getFollowed(1, StmtType::STMT).empty());
  }

  SECTION("isFollows") {
    REQUIRE(reader.isFollows(1, 2) == true);
    REQUIRE(reader.isFollows(1, 4) == false);
    REQUIRE(reader.isFollows(3, 5) == false);
  }

  SECTION("getFollowsPairs") {
    StrStrPairVec actualVector1 =
        reader.getFollowsPairs(StmtType::STMT, StmtType::STMT);
    StrStrPairVec actualVector2 =
        reader.getFollowsPairs(StmtType::ASSIGN, StmtType::STMT);
    StrStrPairVec actualVector3 =
        reader.getFollowsPairs(StmtType::STMT, StmtType::WHILE);
    StrStrPairVec expectedVector1 =
        StrStrPairVec {{"1", "2"}, {"3", "4"}, {"4", "5"}};
    StrStrPairVec expectedVector2 = StrStrPairVec {{"1", "2"}, {"3", "4"}};
    StrStrPairVec expectedVector3 = StrStrPairVec {{"1", "2"}, {"4", "5"}};
    REQUIRE(compareVectorContents(actualVector1, expectedVector1));
    REQUIRE(compareVectorContents(actualVector2, expectedVector2));
    REQUIRE(compareVectorContents(actualVector3, expectedVector3));
    REQUIRE(reader.getFollowsPairs(StmtType::READ, StmtType::PRINT).empty());
  }

  SECTION("getAllFollowing") {
    std::vector<std::string> actualVector1 =
        reader.getFollowsStar(1, StmtType::STMT);
    std::vector<std::string> actualVector2 =
        reader.getFollowsStar(3, StmtType::STMT);
    std::vector<std::string> actualVector3 =
        reader.getFollowsStar(3, StmtType::IF);
    std::vector<std::string> actualVector4 =
        reader.getFollowsStar(4, StmtType::STMT);
    std::vector<std::string> expectedVector1 = {"2"};
    std::vector<std::string> expectedVector2 = {"4", "5"};
    std::vector<std::string> expectedVector3 = {"4"};
    std::vector<std::string> expectedVector4 = {"5"};
    REQUIRE(compareVectorContents(actualVector1, expectedVector1));
    REQUIRE(compareVectorContents(actualVector2, expectedVector2));
    REQUIRE(compareVectorContents(actualVector3, expectedVector3));
    REQUIRE(compareVectorContents(actualVector4, expectedVector4));
    REQUIRE(reader.getFollowsStar(3, StmtType::READ).empty());
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
    StrStrPairVec actualVector1 =
        reader.getFollowsStarPairs(StmtType::STMT, StmtType::STMT);
    StrStrPairVec actualVector2 =
        reader.getFollowsStarPairs(StmtType::STMT, StmtType::WHILE);
    StrStrPairVec actualVector3 =
        reader.getFollowsStarPairs(StmtType::ASSIGN, StmtType::STMT);
    StrStrPairVec expectedVector1 =
        StrStrPairVec {{"1", "2"}, {"3", "4"}, {"3", "5"}, {"4", "5"}};
    StrStrPairVec expectedVector2 =
        StrStrPairVec {{"1", "2"}, {"3", "5"}, {"4", "5"}};
    StrStrPairVec expectedVector3 =
        StrStrPairVec {{"1", "2"}, {"3", "4"}, {"3", "5"}};
    REQUIRE(compareVectorContents(actualVector1, expectedVector1));
    REQUIRE(compareVectorContents(actualVector2, expectedVector2));
    REQUIRE(compareVectorContents(actualVector3, expectedVector3));
    REQUIRE(
        reader.getFollowsStarPairs(StmtType::PRINT, StmtType::STMT).empty());
  }

  SECTION("getImmediateChildren") {
    std::vector<std::string> actualVector1 =
        reader.getImmediateChildrenOf(1, StmtType::STMT);
    std::vector<std::string> actualVector2 =
        reader.getImmediateChildrenOf(3, StmtType::STMT);
    std::vector<std::string> actualVector3 =
        reader.getImmediateChildrenOf(3, StmtType::IF);
    std::vector<std::string> expectedVector1 = {"2", "3"};
    std::vector<std::string> expectedVector2 = {"4", "5"};
    std::vector<std::string> expectedVector3 = {"4"};
    REQUIRE(compareVectorContents(actualVector1, expectedVector1));
    REQUIRE(compareVectorContents(actualVector2, expectedVector2));
    REQUIRE(compareVectorContents(actualVector3, expectedVector3));
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
    StrStrPairVec actualVector1 =
        reader.getParentChildPairs(StmtType::STMT, StmtType::STMT);
    StrStrPairVec expectedVector1 =
        StrStrPairVec {{"1", "2"}, {"1", "3"}, {"3", "4"}, {"3", "5"}};
    REQUIRE(compareVectorContents(actualVector1, expectedVector1));
    REQUIRE(reader.getParentChildPairs(StmtType::READ, StmtType::STMT).empty());
  }

  SECTION("getChildrenStar") {
    std::vector<std::string> actualVector1 =
        reader.getChildrenStarOf(1, StmtType::STMT);
    std::vector<std::string> actualVector2 =
        reader.getChildrenStarOf(1, StmtType::WHILE);
    std::vector<std::string> actualVector3 =
        reader.getChildrenStarOf(3, StmtType::STMT);
    std::vector<std::string> expectedVector1 = {"2", "3", "4", "5"};
    std::vector<std::string> expectedVector2 = {"2", "5"};
    std::vector<std::string> expectedVector3 = {"4", "5"};
    REQUIRE(compareVectorContents(actualVector1, expectedVector1));
    REQUIRE(compareVectorContents(actualVector2, expectedVector2));
    REQUIRE(compareVectorContents(actualVector3, expectedVector3));
    REQUIRE(reader.getChildrenStarOf(1, StmtType::READ).empty());
    REQUIRE(reader.getChildrenStarOf(2, StmtType::STMT).empty());
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
    StrStrPairVec actualVector1 =
        reader.getParentChildStarPairs(StmtType::STMT, StmtType::STMT);
    StrStrPairVec actualVector2 =
        reader.getParentChildStarPairs(StmtType::ASSIGN, StmtType::STMT);
    StrStrPairVec actualVector3 =
        reader.getParentChildStarPairs(StmtType::ASSIGN, StmtType::WHILE);
    StrStrPairVec expectedVector1 = {{"1", "2"}, {"1", "3"}, {"1", "4"},
                                     {"1", "5"}, {"3", "4"}, {"3", "5"}};
    StrStrPairVec expectedVector2 = {{"1", "2"}, {"1", "3"}, {"1", "4"},
                                     {"1", "5"}, {"3", "4"}, {"3", "5"}};
    StrStrPairVec expectedVector3 = {{"1", "2"}, {"1", "5"}, {"3", "5"}};
    REQUIRE(compareVectorContents(actualVector1, expectedVector1));
    REQUIRE(compareVectorContents(actualVector2, expectedVector2));
    REQUIRE(compareVectorContents(actualVector3, expectedVector3));
    REQUIRE(
        reader.getParentChildStarPairs(StmtType::READ, StmtType::STMT).empty());
  }

  SECTION("getStatementsModifying") {
    REQUIRE(compareVectorContents(
        reader.getStatementsModifying("x", StmtType::STMT), {"1", "3", "6"}));
    REQUIRE(compareVectorContents(
        reader.getStatementsModifying("x", StmtType::ASSIGN), {"1", "3"}));
    REQUIRE(compareVectorContents(
        reader.getStatementsModifying("x", StmtType::READ), {"6"}));
    REQUIRE(reader.getStatementsModifying("x", StmtType::PRINT).empty());
    REQUIRE(compareVectorContents(
        reader.getStatementsModifying("y", StmtType::STMT), {"2", "5"}));
  }

  SECTION("getVariablesModifiedBy") {
    REQUIRE(compareVectorContents(reader.getVariablesModifiedBy(1), {"x"}));
    REQUIRE(compareVectorContents(reader.getVariablesModifiedBy(2), {"y"}));
    REQUIRE(reader.getVariablesModifiedBy(7).empty());
  }

  SECTION("getStatementsUsing") {
    REQUIRE(compareVectorContents(
        reader.getStatementsUsing("x", StmtType::STMT), {"1", "2", "4"}));
    REQUIRE(compareVectorContents(
        reader.getStatementsUsing("x", StmtType::ASSIGN), {"1"}));
    REQUIRE(reader.getStatementsUsing("x", StmtType::READ).empty());
    REQUIRE(compareVectorContents(
        reader.getStatementsUsing("y", StmtType::STMT), {"1"}));
    REQUIRE(reader.getStatementsUsing("a", StmtType::STMT).empty());
  }

  SECTION("getVariablesUsedBy") {
    REQUIRE(compareVectorContents(reader.getVariablesUsedBy(1), {"x", "y"}));
    REQUIRE(compareVectorContents(reader.getVariablesUsedBy(2), {"x"}));
    REQUIRE(reader.getVariablesUsedBy(7).empty());
  }

  SECTION("getAllModifiedVariables") {
    REQUIRE(compareVectorContents(reader.getModifiesStmtPairs(StmtType::STMT),
                                  {{"1", "x"},
                                   {"3", "x"},
                                   {"6", "x"},
                                   {"2", "y"},
                                   {"5", "y"},
                                   {"4", "z"}}));
    REQUIRE(compareVectorContents(reader.getModifiesStmtPairs(StmtType::ASSIGN),
                                  {{"1", "x"}, {"3", "x"}}));
    REQUIRE(compareVectorContents(reader.getModifiesStmtPairs(StmtType::IF),
                                  {{"4", "z"}}));
    REQUIRE(reader.getModifiesStmtPairs(StmtType::PRINT).empty());
  }

  SECTION("getUsesStmtPairs") {
    REQUIRE(compareVectorContents(
        reader.getUsesStmtPairs(StmtType::STMT),
        {{"1", "x"}, {"2", "x"}, {"4", "x"}, {"1", "y"}, {"3", "z"}}));
    REQUIRE(compareVectorContents(reader.getUsesStmtPairs(StmtType::ASSIGN),
                                  {{"1", "x"}, {"1", "y"}, {"3", "z"}}));
    REQUIRE(compareVectorContents(reader.getUsesStmtPairs(StmtType::IF),
                                  {{"4", "x"}}));
    REQUIRE(reader.getUsesStmtPairs(StmtType::PRINT).empty());
  }

  SECTION("getExactAssignPattern") {
    StrStrPairVec resultVector1 =
        reader.getExactAssignPattern("x", " a b c * + ");
    StrStrPairVec resultVector2 = reader.getExactAssignPattern("x", " b ");
    StrStrPairVec resultVector3 =
        reader.getExactAssignPattern("y", " d e + f + ");
    StrStrPairVec resultVector4 =
        reader.getExactAssignPattern("z", " a b c * + ");
    StrStrPairVec resultVector5 =
        reader.getExactAssignPattern("_", " a b c * + ");
    StrStrPairVec resultVector6 = reader.getExactAssignPattern("_", "_");
    StrStrPairVec resultVector7 = reader.getExactAssignPattern("x", "_");
    REQUIRE(compareVectorContents(resultVector1, {{"1", "x"}}));
    REQUIRE(resultVector2.empty());
    REQUIRE(compareVectorContents(resultVector3, {{"2", "y"}}));
    REQUIRE(resultVector4.empty());
    REQUIRE(compareVectorContents(resultVector5, {{"1", "x"}}));
    REQUIRE(compareVectorContents(
        resultVector6, {{"1", "x"}, {"2", "y"}, {"3", "z"}, {"4", "x"}}));
    REQUIRE(compareVectorContents(resultVector7, {{"1", "x"}, {"4", "x"}}));
  }

  SECTION("getPartialAssignPattern") {
    StrStrPairVec resultVector1 =
        reader.getPartialAssignPattern("x", " a b c * + ");
    StrStrPairVec resultVector2 = reader.getPartialAssignPattern("x", " 2 ");
    StrStrPairVec resultVector3 = reader.getPartialAssignPattern("x", " 3 ");
    StrStrPairVec resultVector4 = reader.getPartialAssignPattern("_", " a ");
    StrStrPairVec resultVector5 = reader.getPartialAssignPattern("_", " a ");
    StrStrPairVec resultVector6 = reader.getPartialAssignPattern("x", "_");
    StrStrPairVec resultVector7 = reader.getPartialAssignPattern("_", "_");
    REQUIRE(compareVectorContents(resultVector1, {{"1", "x"}}));
    REQUIRE(compareVectorContents(resultVector2, {{"4", "x"}}));
    REQUIRE(resultVector3.empty());
    REQUIRE(compareVectorContents(resultVector4,
                                  {{"1", "x"}, {"3", "z"}, {"4", "x"}}));
    REQUIRE(compareVectorContents(resultVector5,
                                  {{"1", "x"}, {"3", "z"}, {"4", "x"}}));
    REQUIRE(compareVectorContents(resultVector6, {{"1", "x"}, {"4", "x"}}));
    REQUIRE(compareVectorContents(
        resultVector7, {{"1", "x"}, {"2", "y"}, {"3", "z"}, {"4", "x"}}));
  }

  SECTION("Test whilePattern") {
    writer.addWhilePattern(6, "x");
    writer.addWhilePattern(6, "y");
    writer.addWhilePattern(7, "y");
    writer.addWhilePattern(8, "x");
    writer.addWhilePattern(8, "z");
    writer.addWhilePattern(9, "x");

    StrStrPairVec resultVec1 = reader.getWhilePattern("x");
    StrStrPairVec resultVec2 = reader.getWhilePattern("y");
    StrStrPairVec resultVec3 = reader.getWhilePattern("z");
    StrStrPairVec resultVec4 = reader.getWhilePattern("_");

    REQUIRE(compareVectorContents(resultVec1,
                                  {{"6", "x"}, {"8", "x"}, {"9", "x"}}));
    REQUIRE(compareVectorContents(resultVec2, {{"6", "y"}, {"7", "y"}}));
    REQUIRE(compareVectorContents(resultVec3, {{"8", "z"}}));
    REQUIRE(compareVectorContents(resultVec4, {{"6", "x"},
                                               {"6", "y"},
                                               {"7", "y"},
                                               {"8", "x"},
                                               {"8", "z"},
                                               {"9", "x"}}));
  }

  SECTION("Test ifPattern") {
    writer.addIfPattern(6, "a");
    writer.addIfPattern(7, "b");
    writer.addIfPattern(8, "c");
    writer.addIfPattern(9, "a");
    writer.addIfPattern(10, "b");
    writer.addIfPattern(11, "d");

    StrStrPairVec resultVec1 = reader.getIfPattern("a");
    StrStrPairVec resultVec2 = reader.getIfPattern("b");
    StrStrPairVec resultVec3 = reader.getIfPattern("c");
    StrStrPairVec resultVec4 = reader.getIfPattern("_");

    REQUIRE(compareVectorContents(resultVec1, {{"6", "a"}, {"9", "a"}}));
    REQUIRE(compareVectorContents(resultVec2, {{"7", "b"}, {"10", "b"}}));
    REQUIRE(compareVectorContents(resultVec3, {{"8", "c"}}));
    REQUIRE(compareVectorContents(resultVec4, {{"6", "a"},
                                               {"7", "b"},
                                               {"8", "c"},
                                               {"9", "a"},
                                               {"10", "b"},
                                               {"11", "d"}}));
  }
}
