#include "catch.hpp"
#include "../../../../spa/src/pkb/facade/PKBReader.h"
#include "../../../../spa/src/pkb/facade/PKBWriter.h"
#include "../../../../spa/src/pkb/facade/PKBStorage.h"

TEST_CASE("PKBReader Tests") {
    PKBStorage storage;
    PKBReader reader(storage);
    PKBWriter writer(storage);

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

    writer.setAssignPattern("x", "abc*+", 1);
    writer.setAssignPattern("y", "de+f+", 2);
    writer.setAssignPattern("z", "ab*c*d+", 3);
    writer.setAssignPattern("x", "a2+", 4);

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
        REQUIRE(reader.getAllModifiedVariables(StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"x", "1"}, { "x", "3" }, { "x", "6" }, { "y", "2" }, { "y", "5" }, { "z", "4" }});
        REQUIRE(reader.getAllModifiedVariables(StmtType::ASSIGN) == std::vector<std::pair<std::string, std::string>>{ {"x", "1"}, { "x", "3" }});
        REQUIRE(reader.getAllModifiedVariables(StmtType::IF) == std::vector<std::pair<std::string, std::string>>{ { "z", "4" }});
        REQUIRE(reader.getAllModifiedVariables(StmtType::PRINT) == std::vector<std::pair<std::string, std::string>>{});
    }

    SECTION("getAllUsedVariables") {
        REQUIRE(reader.getAllUsedVariables(StmtType::STMT) == std::vector<std::pair<std::string, std::string>>{ {"x", "1"}, { "x", "2" }, { "x", "4" }, { "y", "1" }, { "z", "3" }});
        REQUIRE(reader.getAllUsedVariables(StmtType::ASSIGN) == std::vector<std::pair<std::string, std::string>>{ {"x", "1"}, { "y", "1" }, { "z", "3" }});
        REQUIRE(reader.getAllUsedVariables(StmtType::IF) == std::vector<std::pair<std::string, std::string>>{ { "x", "4" }});
        REQUIRE(reader.getAllUsedVariables(StmtType::PRINT) == std::vector<std::pair<std::string, std::string>>{});
    }

    SECTION("getExactAssignPattern") {
        REQUIRE(reader.getExactAssignPattern("x", "abc*+", false) == std::vector<std::string>{"1"});
        REQUIRE(reader.getExactAssignPattern("x", "b", false) == std::vector<std::string>{});
        REQUIRE(reader.getExactAssignPattern("y", "de+f+", false) == std::vector<std::string>{"2"});
        REQUIRE(reader.getExactAssignPattern("z", "abc*+", false) == std::vector<std::string>{});
        REQUIRE(reader.getExactAssignPattern("_", "_", false) == std::vector<std::string>{"1", "2", "3", "4"});
        REQUIRE(reader.getExactAssignPattern("x", "_", false) == std::vector<std::string>{"1", "4"});
    }

    SECTION("getPartialAssignPattern") {
        REQUIRE(reader.getPartialAssignPattern("x", "abc*+", false) == std::vector<std::string>{"1"});
        REQUIRE(reader.getPartialAssignPattern("x", "2", false) == std::vector<std::string>{"4"});
        REQUIRE(reader.getPartialAssignPattern("x", "3", false) == std::vector<std::string>{});
        REQUIRE(reader.getPartialAssignPattern("_", "a", false) == std::vector<std::string>{"1", "3", "4"});
        REQUIRE(reader.getPartialAssignPattern("x", "_", false) == std::vector<std::string>{"1", "4", "5"});
        REQUIRE(reader.getPartialAssignPattern("_", "_", false) == std::vector<std::string>{"1", "2", "3", "4"});
    }
}