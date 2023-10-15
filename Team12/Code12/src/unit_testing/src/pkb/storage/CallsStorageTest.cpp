#include <catch.hpp>

#include "pkb/storage/relation_storage/proc_to_proc/CallsStorage.h"

TEST_CASE("Setting and Getting Calls Relationships") {
  CallsStorage callsStorage;

  callsStorage.setCallsRelationship("proc1", "proc2", 1);
  callsStorage.setCallsRelationship("proc1", "proc3", 2);
  callsStorage.setCallsStarRelationship("proc1", "proc2");
  callsStorage.setCallsStarRelationship("proc1", "proc3");

  SECTION("Get Calls") {
    auto calls = callsStorage.getCalleeProcs("proc1");
    REQUIRE(calls.size() == 2);
  }

  SECTION("Get Calls Star") {
    auto callsStar = callsStorage.getCalleeProcsStar("proc1");
    REQUIRE(callsStar.size() == 2);
  }

  SECTION("Get Called By") {
    auto calledBy = callsStorage.getCallerProcs("proc2");
    REQUIRE(calledBy.size() == 1);
  }

  SECTION("Get Called By Star") {
    auto calledByStar = callsStorage.getCallerProcsStar("proc2");
    REQUIRE(calledByStar.size() == 1);
  }
}

TEST_CASE("Checking Calls Relationships") {
  CallsStorage callsStorage;

  callsStorage.setCallsRelationship("proc1", "proc2", 1);
  callsStorage.setCallsStarRelationship("proc1", "proc2");

  SECTION("Is Calls") {
    REQUIRE(callsStorage.isCalls("proc1", "proc2"));
    REQUIRE(!callsStorage.isCalls("proc1", "proc3"));
    REQUIRE(!callsStorage.isCalls("proc2", "proc1"));
  }

  SECTION("Is Calls Star") {
    REQUIRE(callsStorage.isCallsStar("proc1", "proc2"));
  }
}
