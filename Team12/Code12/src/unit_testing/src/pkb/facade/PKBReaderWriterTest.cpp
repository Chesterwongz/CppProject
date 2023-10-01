#include "catch.hpp"

#include <unordered_set>
#include "../../../../spa/src/pkb/facade/PKBReader.h"
#include "../../../../spa/src/pkb/facade/PKBWriter.h"
#include "../../common/utils/HelperFunctions.h"

TEST_CASE("PKBReader Tests") {
    PKBStorage storage;
    PKBWriter writer(storage);
    PKBReader reader(storage);

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

    SECTION("getAllVariables") {
        REQUIRE(reader.getAllVariables() == std::set<std::string>{"x", "y", "z"});
    }

    SECTION("getAllConstants") {
        writer.setConstant("1");
        writer.setConstant("3");
        writer.setConstant("10");
        REQUIRE(reader.getAllConstants() == std::set<std::string>{"1", "3", "10"});
    }

    SECTION("getAllProcedures") {
        writer.setProcedure("proc1", 1);
        writer.setProcedure("proc2", 5);
        REQUIRE(reader.getAllProcedures() == std::set<std::string>{"proc1", "proc2"});
    }

    SECTION("getStatement") {
        REQUIRE(reader.getStatement(StmtType::ASSIGN) == std::set<std::string>{"1", "3"});
        REQUIRE(reader.getStatement(StmtType::WHILE) == std::set<std::string>{"2", "5"});
        REQUIRE(reader.getStatement(StmtType::IF) == std::set<std::string>{"4"});
        REQUIRE(reader.getStatement(StmtType::READ) == std::set<std::string>{"6"});
        REQUIRE(reader.getStatement(StmtType::STMT) == std::set<std::string>{ "1", "2", "3", "4", "5", "6"});
    }

    SECTION("getFollowing") {
        REQUIRE(reader.getFollowing(1, StmtType::STMT) == "2");
        REQUIRE(reader.getFollowing(3, StmtType::STMT) == "4");
        REQUIRE(reader.getFollowing(4, StmtType::STMT) == "5");
        REQUIRE(reader.getFollowing(5, StmtType::STMT) == "-1");
    }

    SECTION("getFollowed") {
        REQUIRE(reader.getFollowed(2, StmtType::STMT) == "1");
        REQUIRE(reader.getFollowed(5, StmtType::STMT) == "4");
        REQUIRE(reader.getFollowed(4, StmtType::STMT) == "3");
        REQUIRE(reader.getFollowed(1, StmtType::STMT) == "-1");
    }

    SECTION("isFollows") {
        REQUIRE(reader.isFollows(1, 2) == true);
        REQUIRE(reader.isFollows(1, 4) == false);
        REQUIRE(reader.isFollows(3, 5) == false);
    }

    SECTION("getFollowsPairs") {
        REQUIRE(reader.getFollowsPairs(StmtType::STMT, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}, { "3", "4" }, { "4", "5" }});
        REQUIRE(reader.getFollowsPairs(StmtType::ASSIGN, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}, { "3", "4" }});
        REQUIRE(reader.getFollowsPairs(StmtType::STMT, StmtType::WHILE) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}, { "4", "5" }});
        REQUIRE(reader.getFollowsPairs(StmtType::READ, StmtType::PRINT) == std::vector<std::pair<std::string, std::string>>{});
    }

    SECTION("getAllFollowing") {
        REQUIRE(reader.getFollowsStar(1, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}});
        REQUIRE(reader.getFollowsStar(3, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"3", "4"}, { "3", "5" }});
        REQUIRE(reader.getFollowsStar(3, StmtType::IF) == std::vector<std::pair<std::string, std::string>>{ {"3", "4"}});
        REQUIRE(reader.getFollowsStar(3, StmtType::READ) == std::vector<std::pair<std::string, std::string>>{});
        REQUIRE(reader.getFollowsStar(4, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"4", "5"}});
        REQUIRE(reader.getFollowsStar(5, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{});
    }

    SECTION("getAllFollowed") {
        REQUIRE(reader.getFollowedStar(2, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}});
        REQUIRE(reader.getFollowedStar(5, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"3", "5"}, { "4", "5" }});
        REQUIRE(reader.getFollowedStar(5, StmtType::ASSIGN) == std::vector<std::pair<std::string, std::string>>{ {"3", "5"}});
        REQUIRE(reader.getFollowedStar(4, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"3", "4"}});
        REQUIRE(reader.getFollowedStar(4, StmtType::PRINT) == std::vector<std::pair<std::string, std::string>>{});
        REQUIRE(reader.getFollowedStar(1, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{});
    }

    SECTION("isFollowsStar") {
        REQUIRE(reader.isFollowsStar(3, 5) == true);
        REQUIRE(reader.isFollowsStar(1, 4) == false);
    }

    SECTION("getFollowsStarPairs") {
        REQUIRE(reader.getFollowsStarPairs(StmtType::STMT, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}, { "3", "4" }, { "3", "5" }, { "4", "5" }});
        REQUIRE(reader.getFollowsStarPairs(StmtType::STMT, StmtType::WHILE) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}, { "3", "5" }, { "4", "5" }});
        REQUIRE(reader.getFollowsStarPairs(StmtType::ASSIGN, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}, { "3", "4" }, { "3", "5" }});
        REQUIRE(reader.getFollowsStarPairs(StmtType::PRINT, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{});
    }

    SECTION("getImmediateChildren") {
        REQUIRE(reader.getImmediateChildrenOf(1, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}, { "1", "3" }});
        REQUIRE(reader.getImmediateChildrenOf(3, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"3", "4"}, { "3", "5" }});
        REQUIRE(reader.getImmediateChildrenOf(3, StmtType::IF) == std::vector<std::pair<std::string, std::string>>{ {"3", "4"}});
        REQUIRE(reader.getImmediateChildrenOf(3, StmtType::READ) == std::vector<std::pair<std::string, std::string>>{});
        REQUIRE(reader.getImmediateChildrenOf(4, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{});
    }

    SECTION("getImmediateParent") {
        REQUIRE(reader.getImmediateParentOf(2, StmtType::STMT) == std::pair<std::string, std::string>{"1", "2"});
        REQUIRE(reader.getImmediateParentOf(3, StmtType::STMT) == std::pair<std::string, std::string>{"1", "3"});
        REQUIRE(reader.getImmediateParentOf(3, StmtType::ASSIGN) == std::pair<std::string, std::string>{"1", "3"});
        REQUIRE(reader.getImmediateParentOf(3, StmtType::READ) == std::pair<std::string, std::string>{});
        REQUIRE(reader.getImmediateParentOf(3, StmtType::CALL) == std::pair<std::string, std::string>{});
        REQUIRE(reader.getImmediateParentOf(4, StmtType::STMT) == std::pair<std::string, std::string>{"3", "4"});
        REQUIRE(reader.getImmediateParentOf(5, StmtType::STMT) == std::pair<std::string, std::string>{"3", "5"});
    }

    SECTION("isParent") {
        REQUIRE(reader.isParent(1, 3) == true);
        REQUIRE(reader.isParent(1, 4) == false);
        REQUIRE(reader.isParent(3, 4) == true);
    }

    SECTION("getParentChildPairs") {
        REQUIRE(reader.getParentChildPairs(StmtType::STMT, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}, { "1", "3" }, { "3", "4" }, { "3", "5" }});
        REQUIRE(reader.getParentChildPairs(StmtType::READ, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{});
    }

    SECTION("getChildrenStar") {
        REQUIRE(reader.getChildrenStarOf(1, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}, { "1", "3" }, { "1", "4" }, { "1", "5" }});
        REQUIRE(reader.getChildrenStarOf(1, StmtType::WHILE) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}, { "1", "5" }});
        REQUIRE(reader.getChildrenStarOf(1, StmtType::READ) == std::vector<std::pair<std::string, std::string>>{});
        REQUIRE(reader.getChildrenStarOf(2, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{});
        REQUIRE(reader.getChildrenStarOf(3, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ { "3", "4" }, { "3", "5" }});
        REQUIRE(reader.getChildrenStarOf(5, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{});
    }

    SECTION("getParentStar") {
        REQUIRE(reader.getParentStarOf(1, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{});
        REQUIRE(reader.getParentStarOf(2, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}});
        REQUIRE(reader.getParentStarOf(2, StmtType::ASSIGN) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}});
        REQUIRE(reader.getParentStarOf(2, StmtType::READ) == std::vector<std::pair<std::string, std::string>>{});
        REQUIRE(reader.getParentStarOf(4, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "4"}, { "3", "4" }});
        REQUIRE(reader.getParentStarOf(4, StmtType::ASSIGN) == std::vector<std::pair<std::string, std::string>>{ {"1", "4"}, { "3", "4" }});
        REQUIRE(reader.getParentStarOf(5, StmtType::PRINT) == std::vector<std::pair<std::string, std::string>>{});
    }

    SECTION("isParentStar") {
        REQUIRE(reader.isParentStar(1, 3) == true);
        REQUIRE(reader.isParentStar(1, 5) == true);
        REQUIRE(reader.isParentStar(2, 3) == false);
    }

    SECTION("getParentChildStarPairs") {
        REQUIRE(reader.getParentChildStarPairs(StmtType::STMT, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}, { "1", "3" }, { "1", "4" }, { "1", "5" }, { "3", "4" }, { "3", "5" }});
        REQUIRE(reader.getParentChildStarPairs(StmtType::READ, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{});
        REQUIRE(reader.getParentChildStarPairs(StmtType::ASSIGN, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}, { "1", "3" }, { "1", "4" }, { "1", "5" }, { "3", "4" }, { "3", "5" }});
        REQUIRE(reader.getParentChildStarPairs(StmtType::ASSIGN, StmtType::WHILE) == std::vector<std::pair<std::string, std::string>>{ {"1", "2"}, { "1", "5" }, { "3", "5" }});
    }

    SECTION("getStatementsModifying") {
        REQUIRE(reader.getStatementsModifying("x", StmtType::STMT) == std::vector<std::string>{"1", "3", "6"});
        REQUIRE(reader.getStatementsModifying("x", StmtType::ASSIGN) == std::vector<std::string>{"1", "3"});
        REQUIRE(reader.getStatementsModifying("x", StmtType::READ) == std::vector<std::string>{"6"});
        REQUIRE(reader.getStatementsModifying("x", StmtType::PRINT) == std::vector<std::string>{});
        REQUIRE(reader.getStatementsModifying("y", StmtType::STMT) == std::vector<std::string>{"2", "5"});
    }

    SECTION("getVariablesModifiedBy") {
        REQUIRE(reader.getVariablesModifiedBy(1, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "x"}});
        REQUIRE(reader.getVariablesModifiedBy(2, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"2", "y"}});
        REQUIRE(reader.getVariablesModifiedBy(7, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{});
    }

    SECTION("getStatementsUsing") {
        REQUIRE(reader.getStatementsUsing("x", StmtType::STMT) == std::vector<std::string>{"1", "2", "4"});
        REQUIRE(reader.getStatementsUsing("x", StmtType::ASSIGN) == std::vector<std::string>{"1"});
        REQUIRE(reader.getStatementsUsing("x", StmtType::READ) == std::vector<std::string>{});
        REQUIRE(reader.getStatementsUsing("y", StmtType::STMT) == std::vector<std::string>{"1"});
        REQUIRE(reader.getStatementsUsing("a", StmtType::STMT) == std::vector<std::string>{});
    }

    SECTION("getVariablesUsedBy") {
        REQUIRE(reader.getVariablesUsedBy(1, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "x"}, { "1", "y" }});
        REQUIRE(reader.getVariablesUsedBy(1, StmtType::ASSIGN) == std::vector<std::pair<std::string, std::string>>{ {"1", "x"}, { "1", "y" }});
        REQUIRE(reader.getVariablesUsedBy(1, StmtType::PRINT) == std::vector<std::pair<std::string, std::string>>{});
        REQUIRE(reader.getVariablesUsedBy(2, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"2", "x"}});
        REQUIRE(reader.getVariablesUsedBy(7, StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{});
    }

    SECTION("getAllModifiedVariables") {
        REQUIRE(reader.getAllModifiedVariables(StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{{"1", "x"}, { "3", "x" }, { "6", "x" }, { "2", "y" }, { "5", "y" }, { "4", "z" }});
        REQUIRE(reader.getAllModifiedVariables(StmtType::ASSIGN) == std::vector<std::pair<std::string, std::string>>{ {"1", "x"}, { "3", "x" }});
        REQUIRE(reader.getAllModifiedVariables(StmtType::IF) == std::vector<std::pair<std::string, std::string>>{ { "4", "z" }});
        REQUIRE(reader.getAllModifiedVariables(StmtType::PRINT) == std::vector<std::pair<std::string, std::string>>{});
    }

    SECTION("getAllUsedVariables") {
        REQUIRE(reader.getAllUsedVariables(StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"1", "x"}, { "2", "x" }, { "4", "x" }, { "1", "y" }, { "3", "z" }});
        REQUIRE(reader.getAllUsedVariables(StmtType::ASSIGN) == std::vector<std::pair<std::string, std::string>>{ {"1", "x"}, { "1", "y" }, { "3", "z" }});
        REQUIRE(reader.getAllUsedVariables(StmtType::IF) == std::vector<std::pair<std::string, std::string>>{ { "4", "x" }});
        REQUIRE(reader.getAllUsedVariables(StmtType::PRINT).empty());
    }

    SECTION("getExactAssignPattern") {
        std::vector<std::string> resultVector1 = reader.getExactAssignPattern("x", " a b c * + ", false);
        std::unordered_set<std::string> actual1 = convertStringVectorToUnorderedSet(resultVector1);
        std::vector<std::string> resultVector2 = reader.getExactAssignPattern("x", " b ", false);
        std::unordered_set<std::string> actual2 = convertStringVectorToUnorderedSet(resultVector2);
        std::vector<std::string> resultVector3 = reader.getExactAssignPattern("y", " d e + f + ", false);
        std::unordered_set<std::string> actual3 = convertStringVectorToUnorderedSet(resultVector3);
        std::vector<std::string> resultVector4 = reader.getExactAssignPattern("z", " a b c * + ", false);
        std::unordered_set<std::string> actual4 = convertStringVectorToUnorderedSet(resultVector4);
        std::vector<std::string> resultVector5 = reader.getExactAssignPattern("v", " a b c * + ", true);
        std::unordered_set<std::string> actual5 = convertStringVectorToUnorderedSet(resultVector5);
        std::vector<std::string> resultVector6 = reader.getExactAssignPattern("_", "_", false);
        std::unordered_set<std::string> actual6 = convertStringVectorToUnorderedSet(resultVector6);
        std::vector<std::string> resultVector7 = reader.getExactAssignPattern("x", "_", false);
        std::unordered_set<std::string> actual7 = convertStringVectorToUnorderedSet(resultVector7);
        REQUIRE(actual1 == std::unordered_set<std::string>{"1"});
        REQUIRE(actual2.empty());
        REQUIRE(actual3 == std::unordered_set<std::string>{"2"});
        REQUIRE(actual4.empty());
        REQUIRE(actual5 == std::unordered_set<std::string>{"1"});
        REQUIRE(actual6 == std::unordered_set<std::string>{"1", "2", "3", "4"});
        REQUIRE(actual7 == std::unordered_set<std::string>{"1", "4"});
    }

    SECTION("getPartialAssignPattern") {
        std::vector<std::string> resultVector1 = reader.getPartialAssignPattern("x", " a b c * + ", false);
        std::unordered_set<std::string> actual1 = convertStringVectorToUnorderedSet(resultVector1);
        std::vector<std::string> resultVector2 = reader.getPartialAssignPattern("x", " 2 ", false);
        std::unordered_set<std::string> actual2 = convertStringVectorToUnorderedSet(resultVector2);
        std::vector<std::string> resultVector3 = reader.getPartialAssignPattern("x", " 3 ", false);
        std::unordered_set<std::string> actual3 = convertStringVectorToUnorderedSet(resultVector3);
        std::vector<std::string> resultVector4 = reader.getPartialAssignPattern("v", " a ", true);
        std::unordered_set<std::string> actual4 = convertStringVectorToUnorderedSet(resultVector4);
        std::vector<std::string> resultVector5 = reader.getPartialAssignPattern("_", " a ", false);
        std::unordered_set<std::string> actual5 = convertStringVectorToUnorderedSet(resultVector5);
        std::vector<std::string> resultVector6 = reader.getPartialAssignPattern("x", "_", false);
        std::unordered_set<std::string> actual6 = convertStringVectorToUnorderedSet(resultVector6);
        std::vector<std::string> resultVector7 = reader.getPartialAssignPattern("v", "_", true);
        std::unordered_set<std::string> actual7 = convertStringVectorToUnorderedSet(resultVector7);
        std::vector<std::string> resultVector8 = reader.getPartialAssignPattern("_", "_", false);
        std::unordered_set<std::string> actual8 = convertStringVectorToUnorderedSet(resultVector8);

        REQUIRE(actual1 == std::unordered_set<std::string>{"1"});
        REQUIRE(actual2 == std::unordered_set<std::string>{"4"});
        REQUIRE(actual3.empty());
        REQUIRE(actual4 == std::unordered_set<std::string>{"1", "3", "4"});
        REQUIRE(actual5 == std::unordered_set<std::string>{"1", "3", "4"});
        REQUIRE(actual6 == std::unordered_set<std::string>{"1", "4"});
        REQUIRE(actual7 == std::unordered_set<std::string>{"1", "2", "3", "4"});
        REQUIRE(actual8 == std::unordered_set<std::string>{"1", "2", "3", "4"});
    }
}
