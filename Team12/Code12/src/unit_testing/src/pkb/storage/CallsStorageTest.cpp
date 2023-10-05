#include "catch.hpp"
#include "pkb/storage/CallsStorage.h"

TEST_CASE("Setting and Getting Calls Relationships") {
    CallsStorage callsStorage;

    callsStorage.setCallsRelationship("proc1", "proc2", 1);
    callsStorage.setCallsRelationship("proc1", "proc3", 2);
    callsStorage.setCallsStarRelationship("proc1", "proc2", 1);
    callsStorage.setCallsStarRelationship("proc1", "proc3", 2);

    SECTION("Get Calls") {
        auto calls = callsStorage.getCalls("proc1");
        REQUIRE(calls.size() == 2);
    }

    SECTION("Get Calls Star") {
        auto callsStar = callsStorage.getCallsStar("proc1");
        REQUIRE(callsStar.size() == 2);
    }

    SECTION("Get Called By") {
        auto calledBy = callsStorage.getCalledBy("proc2");
        REQUIRE(calledBy.size() == 1);

    }

    SECTION("Get Called By Star") {
        auto calledByStar = callsStorage.getCalledByStar("proc2");
        REQUIRE(calledByStar.size() == 1);
    }
}

TEST_CASE("Checking Calls Relationships") {
    CallsStorage callsStorage;

    callsStorage.setCallsRelationship("proc1", "proc2", 1);
    callsStorage.setCallsStarRelationship("proc1", "proc2", 1);

    SECTION("Is Calls") {
        REQUIRE(callsStorage.isCalls("proc1", "proc2"));
        REQUIRE(!callsStorage.isCalls("proc1", "proc3"));
        REQUIRE(!callsStorage.isCalls("proc2", "proc1"));
    }

    SECTION("Is Calls Star") {
        REQUIRE(callsStorage.isCallsStar("proc1", "proc2"));
    }
}

TEST_CASE("Finding Procedures for Statements") {
    CallsStorage callsStorage;

    callsStorage.setCallsRelationship("proc1", "proc2", 1);
    callsStorage.setCallsRelationship("proc1", "proc3", 2);

    SECTION("Get Proc Called On") {
        REQUIRE(callsStorage.getProcCalledOn(1) == "proc2");
        REQUIRE(callsStorage.getProcCalledOn(2) == "proc3");
    }

    SECTION("Get Proc Star Called On") {
        auto procsStarCalledOn = callsStorage.getProcStarCalledOn(1);
        REQUIRE(procsStarCalledOn.size() == 0);
    }
}

TEST_CASE("Checking Calls Statements") {
    CallsStorage callsStorage;

    callsStorage.setCallsRelationship("proc1", "proc2", 1);

    SECTION("Is Calling Stmt") {
        REQUIRE(callsStorage.isCallingStmt(1, "proc2"));
        REQUIRE(!callsStorage.isCallingStmt(1, "proc1"));
        REQUIRE(!callsStorage.isCallingStmt(2, "proc2"));
    }

    SECTION("Is Calling Star Stmt") {
        REQUIRE(!callsStorage.isCallingStarStmt(1, "proc2"));
    }
}