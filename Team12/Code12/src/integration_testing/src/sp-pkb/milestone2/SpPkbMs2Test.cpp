
#include <catch.hpp>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "pkb/facade/PKB.h"
#include "pkb/facade/PKBReader.h"
#include "sp/SourceProcessor.h"

using std::set, std::string, std::unordered_map, std::unordered_set;

using ProcToVarSetMap = unordered_map<string, unordered_set<string>>;
using ProcToStmtProcSetMap =
    unordered_map<string,
                  unordered_set<pair<string, string>, PairUtils::PairHash>>;

void validateModifiesProcVar(PKBReader& reader, const vector<string>& procs,
                             ProcToVarSetMap expectedModifiesMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedModifies = expectedModifiesMap[proc];
    std::cout << "proc: " << proc << std::endl;
    std::cout << "expectedModifies: ";
    for (const string& var : expectedModifies) {
      std::cout << var << ", ";
    }
    std::cout << std::endl << "-------------" << std::endl;

    unordered_set<string> actualModifies =
        reader.getModifiedVariablesForProc(proc);
    std::cout << "actualModifies: ";
    for (const string& var : actualModifies) {
      std::cout << var << ", ";
    }
    std::cout << std::endl << "-------------" << std::endl;
    REQUIRE(actualModifies == expectedModifies);
  }
}

void validateUsesProcVar(PKBReader& reader, const vector<string>& procs,
                         ProcToVarSetMap expectedUsesMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedUses = expectedUsesMap[proc];
    std::cout << "proc: " << proc << std::endl;
    std::cout << "expectedUses: ";
    for (const string& var : expectedUses) {
      std::cout << var << ", ";
    }
    std::cout << std::endl << "-------------" << std::endl;

    unordered_set<string> actualUses = reader.getUsedVariablesForProc(proc);
    std::cout << "actualUses: ";
    for (const string& var : actualUses) {
      std::cout << var << ", ";
    }
    std::cout << std::endl << "-------------" << std::endl;
    REQUIRE(actualUses == expectedUses);
  }
}

void validateCalls(PKBReader& reader, const vector<string>& procs,
                   ProcToStmtProcSetMap expectedCallsMap) {
  for (const string& proc : procs) {
    unordered_set<pair<string, string>, PairUtils::PairHash> expectedCalls =
        expectedCallsMap[proc];

    std::cout << "proc: " << proc << std::endl;
    std::cout << "expectedCalls: ";
    for (const auto& [stmtNum, callee] : expectedCalls) {
      std::cout << "(" << stmtNum << ", " << callee << "), ";
    }
    std::cout << std::endl << "-------------" << std::endl;

    vector<pair<string, string>> actualCalls = reader.getCalledBy(proc);
    unordered_set<pair<string, string>, PairUtils::PairHash> actualCallsSet;
    for (const auto& pair : actualCalls) {
      actualCallsSet.insert(pair);
    }
    std::cout << "actualCalls: ";
    for (const auto& [stmtNum, callee] : actualCalls) {
      std::cout << "(" << stmtNum << ", " << callee << "), ";
    }
    std::cout << std::endl << "-------------" << std::endl;
    REQUIRE(actualCallsSet == expectedCalls);
  }
}

void validateCallsStar(PKBReader& reader, const vector<string>& procs,
                       ProcToStmtProcSetMap expectedCallsStarMap) {
  for (const string& proc : procs) {
    unordered_set<pair<string, string>, PairUtils::PairHash> expectedCallsStar =
        expectedCallsStarMap[proc];

    std::cout << "proc: " << proc << std::endl;
    std::cout << "expectedCallsStar: ";
    for (const auto& [stmtNum, callee] : expectedCallsStar) {
      std::cout << "(" << stmtNum << ", " << callee << "), ";
    }
    std::cout << "-------------" << std::endl;

    vector<pair<string, string>> actualCallsStar = reader.getCalledStarBy(proc);
    unordered_set<pair<string, string>, PairUtils::PairHash> actualCallsStarSet;
    for (const auto& pair : actualCallsStar) {
      actualCallsStarSet.insert(pair);
    }
    std::cout << "actualCallsStar: ";
    for (const auto& [stmtNum, callee] : actualCallsStar) {
      std::cout << "(" << stmtNum << ", " << callee << "), ";
    }
    std::cout << "-------------" << std::endl;
    REQUIRE(actualCallsStarSet == expectedCallsStar);
  }
}

TEST_CASE("SP-PKB integration MS2 - Non-nesting statements") {
  string input =
      "procedure simple {"
      "read num1;"     // 1
      "print num2;"    // 2
      "x = num1 + 1;"  // 3
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader& reader = pkb.getReader();

  vector<string> procs = {"simple"};
  ProcToVarSetMap expectedModifiesMap = {{"simple", {"num1", "x"}}};
  ProcToVarSetMap expectedUsesMap = {{"simple", {"num1", "num2"}}};
  ProcToStmtProcSetMap expectedCallsMap = {{"simple", {}}};
  ProcToStmtProcSetMap expectedCallsStarMap = {{"simple", {}}};
  validateUsesProcVar(reader, procs, expectedUsesMap);
  validateModifiesProcVar(reader, procs, expectedModifiesMap);
  validateCalls(reader, procs, expectedCallsMap);
  validateCallsStar(reader, procs, expectedCallsStarMap);
}

TEST_CASE("SP-PKB integration MS2 - Nested statements") {
  string input =
      "procedure A {"
      "call B; }"  // 1
      ""
      "procedure B {"
      "x = 5;"     // 2
      "call C; }"  // 3
      ""
      "procedure C {"
      "y = 10; }";  // 4

  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader& reader = pkb.getReader();

  vector<string> procs = {"A", "B", "C"};
  ProcToVarSetMap expectedModifiesMap = {{"A", {}}, {"B", {"x"}}, {"C", {"y"}}};
  ProcToVarSetMap expectedUsesMap = {{"A", {}}, {"B", {}}, {"C", {}}};
  ProcToStmtProcSetMap expectedCallsMap = {
      {"A", {{"1", "B"}}}, {"B", {{"3", "C"}}}, {"C", {}}};
  ProcToStmtProcSetMap expectedCallsStarMap = {
      {"A", {{"1", "B"}, {"3", "C"}}}, {"B", {{"3", "C"}}}, {"C", {}}};
  validateUsesProcVar(reader, procs, expectedUsesMap);
  validateModifiesProcVar(reader, procs, expectedModifiesMap);
  validateCalls(reader, procs, expectedCallsMap);
  validateCallsStar(reader, procs, expectedCallsStarMap);
}
