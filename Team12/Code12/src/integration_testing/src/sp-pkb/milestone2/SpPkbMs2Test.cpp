
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
using StmtProcPairsSet =
    unordered_set<pair<string, string>, PairUtils::PairHash>;
using ProcToStmtProcSetMap = unordered_map<string, StmtProcPairsSet>;

void printVars(const string& abstraction, const unordered_set<string>& set) {
  std::cout << abstraction << ": ";
  for (const string& var : set) {
    std::cout << var << ", ";
  }
  std::cout << std::endl << "-------------" << std::endl;
}

void printStmtProcPairs(const string& abstraction,
                        const StmtProcPairsSet& set) {
  std::cout << abstraction << ": ";
  for (const auto& [stmtNum, proc] : set) {
    std::cout << "(" << stmtNum << ", " << proc << "), ";
  }
  std::cout << std::endl << "-------------" << std::endl;
}

void validateModifiesProcVar(PKBReader& reader, const vector<string>& procs,
                             ProcToVarSetMap expectedModifiesMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedModifies = expectedModifiesMap[proc];
    std::cout << "proc: " << proc << std::endl;
    printVars("expectedModifies", expectedModifies);
    unordered_set<string> actualModifies =
        reader.getModifiedVariablesForProc(proc);
    printVars("actualModifies", actualModifies);
    REQUIRE(actualModifies == expectedModifies);
  }
}

void validateUsesProcVar(PKBReader& reader, const vector<string>& procs,
                         ProcToVarSetMap expectedUsesMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedUses = expectedUsesMap[proc];
    std::cout << "proc: " << proc << std::endl;
    printVars("expectedUses", expectedUses);
    unordered_set<string> actualUses = reader.getUsedVariablesForProc(proc);
    printVars("actualUses", actualUses);
    REQUIRE(actualUses == expectedUses);
  }
}

void validateCalls(PKBReader& reader, const vector<string>& procs,
                   ProcToStmtProcSetMap expectedCallsMap) {
  for (const string& proc : procs) {
    StmtProcPairsSet expectedCalls = expectedCallsMap[proc];

    std::cout << "proc: " << proc << std::endl;
    printStmtProcPairs("expectedCalls", expectedCalls);

    vector<pair<string, string>> actualCalls = reader.getCalleeProcs(proc);
    StmtProcPairsSet actualCallsSet;
    for (const auto& pair : actualCalls) {
      actualCallsSet.insert(pair);
    }
    printStmtProcPairs("actualCalls", actualCallsSet);
    REQUIRE(actualCallsSet == expectedCalls);
  }
}

void validateCallsStar(PKBReader& reader, const vector<string>& procs,
                       ProcToStmtProcSetMap expectedCallsStarMap) {
  for (const string& proc : procs) {
    StmtProcPairsSet expectedCallsStar = expectedCallsStarMap[proc];

    std::cout << "proc: " << proc << std::endl;
    printStmtProcPairs("expectedCallsStar", expectedCallsStar);

    vector<pair<string, string>> actualCallsStar =
        reader.getCalleeProcsStar(proc);
    StmtProcPairsSet actualCallsStarSet;
    for (const auto& pair : actualCallsStar) {
      actualCallsStarSet.insert(pair);
    }
    printStmtProcPairs("actualCallsStar", actualCallsStarSet);
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
      "x = a + 5;"  // 2
      "call C; }"   // 3
      ""
      "procedure C {"
      "y = 10 - b; }";  // 4

  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader& reader = pkb.getReader();

  vector<string> procs = {"A", "B", "C"};
  ProcToVarSetMap expectedModifiesMap = {
      {"A", {"x", "y"}}, {"B", {"x", "y"}}, {"C", {"y"}}};
  ProcToVarSetMap expectedUsesMap = {
      {"A", {"a", "b"}}, {"B", {"a", "b"}}, {"C", {"b"}}};
  ProcToStmtProcSetMap expectedCallsMap = {
      {"A", {{"1", "B"}}}, {"B", {{"3", "C"}}}, {"C", {}}};
  ProcToStmtProcSetMap expectedCallsStarMap = {
      {"A", {{"1", "B"}, {"3", "C"}}}, {"B", {{"3", "C"}}}, {"C", {}}};
  validateUsesProcVar(reader, procs, expectedUsesMap);
  validateModifiesProcVar(reader, procs, expectedModifiesMap);
  validateCalls(reader, procs, expectedCallsMap);
  validateCallsStar(reader, procs, expectedCallsStarMap);
}
