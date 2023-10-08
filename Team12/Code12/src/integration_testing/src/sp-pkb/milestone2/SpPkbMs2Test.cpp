#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <catch.hpp>

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

TEST_CASE("SP-PKB integration MS2 - Simple transitive call") {
  string input =
      "procedure A {"
      "call B; "  // 1
      "}"
      "procedure B {"
      "x = a + 5;"  // 2
      "call C; "    // 3
      "}"
      "procedure C {"
      "y = 10 - b;"  // 4
      "}";

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

TEST_CASE("SP-PKB integration MS2 - Simple transitive call with while") {
  string input =
      "procedure X {"
      "read a;"  // 1
      "call Y;"  // 2
      "}"
      "procedure Y {"
      "a = b + 10;"       // 3
      "while (a != 0) {"  // 4
      "    call Z;"       // 5
      "    a = a - 1; }"  // 6
      "}"
      "procedure Z {"  // 7
      "print c;"       // 8
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader& reader = pkb.getReader();

  vector<string> procs = {"X", "Y", "Z"};
  ProcToVarSetMap expectedModifiesMap = {{"X", {"a"}}, {"Y", {"a"}}};
  ProcToVarSetMap expectedUsesMap = {
      {"X", {"a", "b", "c"}}, {"Y", {"a", "b", "c"}}, {"Z", {"c"}}};
  ProcToStmtProcSetMap expectedCallsMap = {
      {"X", {{"2", "Y"}}}, {"Y", {{"5", "Z"}}}, {"Z", {}}};
  ProcToStmtProcSetMap expectedCallsStarMap = {
      {"X", {{"2", "Y"}, {"5", "Z"}}}, {"Y", {{"5", "Z"}}}, {"Z", {}}};
  validateUsesProcVar(reader, procs, expectedUsesMap);
  validateModifiesProcVar(reader, procs, expectedModifiesMap);
  validateCalls(reader, procs, expectedCallsMap);
  validateCallsStar(reader, procs, expectedCallsStarMap);
}

TEST_CASE("SP-PKB integration MS2 - Simple transitive call with if") {
  string input =
      "procedure A {"
      "   if (x == 10) then {"  // 1
      "       call B;"          // 2
      "   } else {"
      "       y = 20;"  // 3
      "   }"
      "}"
      "procedure B {"
      "   z = x + 1;"  // 4
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader& reader = pkb.getReader();

  vector<string> procs = {"A", "B"};
  ProcToVarSetMap expectedModifiesMap = {{"A", {"y", "z"}}, {"B", {"z"}}};
  ProcToVarSetMap expectedUsesMap = {{"A", {"x"}}, {"B", {"x"}}};
  ProcToStmtProcSetMap expectedCallsMap = {{"A", {{"2", "B"}}}, {"B", {}}};
  ProcToStmtProcSetMap expectedCallsStarMap = {{"A", {{"2", "B"}}}, {"B", {}}};
  validateUsesProcVar(reader, procs, expectedUsesMap);
  validateModifiesProcVar(reader, procs, expectedModifiesMap);
  validateCalls(reader, procs, expectedCallsMap);
  validateCallsStar(reader, procs, expectedCallsStarMap);
}

TEST_CASE("SP-PKB integration MS2 - multiple transitive calls") {
  string input =
      "procedure P {"
      "call Q;"  // 1
      "}"
      "procedure Q {"
      "z = y + 1;"  // 2
      "call R;"     // 3
      "}"
      "procedure R {"
      "call S;"  // 4
      "}"
      "procedure S {"
      "z = z + 1;"  // 5
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader& reader = pkb.getReader();

  vector<string> procs = {"P", "Q", "R", "S"};
  ProcToVarSetMap expectedModifiesMap = {
      {"P", {"z"}}, {"Q", {"z"}}, {"R", {"z"}}, {"S", {"z"}}};
  ProcToVarSetMap expectedUsesMap = {
      {"P", {"z", "y"}}, {"Q", {"z", "y"}}, {"R", {"z"}}, {"S", {"z"}}};
  ProcToStmtProcSetMap expectedCallsMap = {
      {"P", {{"1", "Q"}}}, {"Q", {{"3", "R"}}}, {"R", {{"4", "S"}}}, {"S", {}}};
  ProcToStmtProcSetMap expectedCallsStarMap = {
      {"P", {{"1", "Q"}, {"3", "R"}, {"4", "S"}}},
      {"Q", {{"3", "R"}, {"4", "S"}}},
      {"R", {{"4", "S"}}},
      {"S", {}}};
  validateUsesProcVar(reader, procs, expectedUsesMap);
  validateModifiesProcVar(reader, procs, expectedModifiesMap);
  validateCalls(reader, procs, expectedCallsMap);
  validateCallsStar(reader, procs, expectedCallsStarMap);
}

TEST_CASE("SP-PKB integration MS2 - multiple calls without transitivity") {
  string input =
      "procedure Alpha {"
      "call Beta;"   // 1
      "call Gamma;"  // 2
      "}"
      "procedure Beta {"
      "b = y + 5;"  // 3
      "}"
      "procedure Gamma {"
      "g = z + 10;"  // 4
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader& reader = pkb.getReader();

  vector<string> procs = {"Alpha", "Beta", "Gamma"};
  ProcToVarSetMap expectedModifiesMap = {
      {"Alpha", {"b", "g"}}, {"Beta", {"b"}}, {"Gamma", {"g"}}};
  ProcToVarSetMap expectedUsesMap = {
      {"Alpha", {"y", "z"}}, {"Beta", {"y"}}, {"Gamma", {"z"}}};
  ProcToStmtProcSetMap expectedCallsMap = {
      {"Alpha", {{"1", "Beta"}, {"2", "Gamma"}}}, {"Beta", {}}, {"Gamma", {}}};
  ProcToStmtProcSetMap expectedCallsStarMap = {
      {"Alpha", {{"1", "Beta"}, {"2", "Gamma"}}}, {"Beta", {}}, {"Gamma", {}}};
  validateUsesProcVar(reader, procs, expectedUsesMap);
  validateModifiesProcVar(reader, procs, expectedModifiesMap);
  validateCalls(reader, procs, expectedCallsMap);
  validateCallsStar(reader, procs, expectedCallsStarMap);
}

TEST_CASE("SP-PKB integration MS2 - two chained calls and containers") {
  string input =
      "procedure Main {"
      "   read a;"             // 1
      "   while (a < 10) {"    // 2
      "       b = a + 2;"      // 3
      "       call Helper; }"  // 4
      "   print b;"            // 5
      "}"
      "procedure Helper {"
      "   if (b > 5) then {"  // 6
      "       a = a + 1;"     // 7
      "   } else {"           // 8
      "       a = a - 1; }"   // 9
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader& reader = pkb.getReader();

  vector<string> procs = {"Main", "Helper"};
  ProcToVarSetMap expectedModifiesMap = {{"Main", {"a", "b"}},
                                         {"Helper", {"a"}}};
  ProcToVarSetMap expectedUsesMap = {{"Main", {"a", "b"}},
                                     {"Helper", {"a", "b"}}};
  ProcToStmtProcSetMap expectedCallsMap = {{"Main", {{"4", "Helper"}}},
                                           {"Helper", {}}};
  ProcToStmtProcSetMap expectedCallsStarMap = {{"Main", {{"4", "Helper"}}},
                                               {"Helper", {}}};
  validateUsesProcVar(reader, procs, expectedUsesMap);
  validateModifiesProcVar(reader, procs, expectedModifiesMap);
  validateCalls(reader, procs, expectedCallsMap);
  validateCallsStar(reader, procs, expectedCallsStarMap);
}

TEST_CASE("SP-PKB integration MS2 - three chained calls and containers") {
  string input =
      "procedure Start {"
      "   read k;"                 // 1
      "   i = a + b % 2 - c / d;"  // 2
      "   call Operate;"           // 3
      "}"
      "procedure Operate {"
      "   while ((p + q * 2) == (x - y % 3)) {"  // 4
      "       call Increment;"                   // 5
      "   }"
      "}"
      "procedure Increment {"
      "   i = i * j + k + 1;"  // 6
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader& reader = pkb.getReader();

  vector<string> procs = {"Start", "Operate", "Increment"};
  ProcToVarSetMap expectedModifiesMap = {
      {"Start", {"i", "k"}}, {"Operate", {"i"}}, {"Increment", {"i"}}};
  ProcToVarSetMap expectedUsesMap = {
      {"Start", {"p", "q", "x", "y", "i", "j", "k", "a", "b", "c", "d"}},
      {"Operate", {"p", "q", "x", "y", "i", "j", "k"}},
      {"Increment", {"i", "j", "k"}}};
  ProcToStmtProcSetMap expectedCallsMap = {{"Start", {{"3", "Operate"}}},
                                           {"Operate", {{"5", "Increment"}}},
                                           {"Increment", {}}};
  ProcToStmtProcSetMap expectedCallsStarMap = {
      {"Start", {{"3", "Operate"}, {"5", "Increment"}}},
      {"Operate", {{"5", "Increment"}}},
      {"Increment", {}}};
  validateUsesProcVar(reader, procs, expectedUsesMap);
  validateModifiesProcVar(reader, procs, expectedModifiesMap);
  validateCalls(reader, procs, expectedCallsMap);
  validateCallsStar(reader, procs, expectedCallsStarMap);
}

TEST_CASE("SP-PKB integration MS2 - nested calls with deep dependencies") {
  string input =
      "procedure Alpha {"
      "    read w;"     // 1
      "    m = 5 + w;"  // 2
      "    call Beta;"  // 3
      "}"
      "procedure Beta {"
      "    if (m > 10) then {"  // 4
      "        n = m - 5;"      // 5
      "        call Gamma;"     // 6
      "    } else {"
      "        call Delta;"   // 7
      "        n = m + 5; }"  // 8
      "    print n;"          // 9
      "}"
      "procedure Gamma {"
      "    o = n + 2;"     // 10
      "    call Epsilon;"  // 11
      "}"
      "procedure Delta {"
      "    p = n * 3;"  // 12
      "}"
      "procedure Epsilon {"
      "    read q;"     // 13
      "    r = o - q;"  // 14
      "    call Zeta;"  // 15
      "}"
      "procedure Zeta {"
      "    print r;"   // 16
      "    call Eta;"  // 17
      "}"
      "procedure Eta {"
      "    read s;"     // 18
      "    t = r + s;"  // 19
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader& reader = pkb.getReader();

  vector<string> procs = {"Alpha",   "Beta", "Gamma", "Delta",
                          "Epsilon", "Zeta", "Eta"};
  ProcToVarSetMap expectedModifiesMap = {
      {"Alpha", {"w", "m", "n", "o", "q", "r", "s", "t", "p"}},
      {"Beta", {"n", "o", "q", "r", "s", "t", "p"}},
      {"Gamma", {"o", "q", "r", "s", "t"}},
      {"Delta", {"p"}},
      {"Epsilon", {"q", "r", "s", "t"}},
      {"Zeta", {"s", "t"}},
      {"Eta", {"s", "t"}}};
  ProcToVarSetMap expectedUsesMap = {
      {"Alpha", {"w", "o", "q", "r", "s", "m", "n"}},
      {"Beta", {"m", "n", "o", "q", "r", "s"}},
      {"Gamma", {"n", "o", "q", "r", "s"}},
      {"Delta", {"n"}},
      {"Epsilon", {"o", "q", "r", "s"}},
      {"Zeta", {"r", "s"}},
      {"Eta", {"r", "s"}}};
  ProcToStmtProcSetMap expectedCallsMap = {
      {"Alpha", {{"3", "Beta"}}},
      {"Beta", {{"6", "Gamma"}, {"7", "Delta"}}},
      {"Gamma", {{"11", "Epsilon"}}},
      {"Delta", {}},
      {"Epsilon", {{"15", "Zeta"}}},
      {"Zeta", {{"17", "Eta"}}},
      {"Eta", {}}};
  ProcToStmtProcSetMap expectedCallsStarMap = {
      {"Alpha",
       {{"3", "Beta"},
        {"6", "Gamma"},
        {"7", "Delta"},
        {"11", "Epsilon"},
        {"15", "Zeta"},
        {"17", "Eta"}}},
      {"Beta",
       {{"6", "Gamma"},
        {"7", "Delta"},
        {"11", "Epsilon"},
        {"15", "Zeta"},
        {"17", "Eta"}}},
      {"Gamma", {{"11", "Epsilon"}, {"15", "Zeta"}, {"17", "Eta"}}},
      {"Delta", {}},
      {"Epsilon", {{"15", "Zeta"}, {"17", "Eta"}}},
      {"Zeta", {{"17", "Eta"}}},
      {"Eta", {}}};
  validateUsesProcVar(reader, procs, expectedUsesMap);
  validateModifiesProcVar(reader, procs, expectedModifiesMap);
  validateCalls(reader, procs, expectedCallsMap);
  validateCallsStar(reader, procs, expectedCallsStarMap);
}

TEST_CASE(
    "SP-PKB integration MS2 - complex nesting with loops and multiple calls") {
  string input =
      "procedure Init {"
      "    read h;"                      // 1
      "    u = h * 2;"                   // 2
      "    while ((c + d) > (e - f)) {"  // 3
      "        call Process;"            // 4
      "        u = u - 5;"               // 5
      "    }"
      "}"
      "procedure Process {"
      "    if ((a * b - (p + q * r / d % f)) == (c / d)) then {"  // 6
      "        call Finish;"                                      // 7
      "    } else {"
      "        call Clean;"   // 8
      "        v = u + 5;"    // 9
      "        call Update;"  // 10
      "    }"
      "    print v;"  // 11
      "}"
      "procedure Clean {"
      "    u = 0;"  // 12
      "}"
      "procedure Finish {"
      "    read j;"  // 13
      "    v = j;"   // 14
      "}"
      "procedure Update {"
      "    v = v + 1;"  // 15
      "}";
  // extract
  SourceProcessor sp;
  PKB pkb;
  sp.processContent(input, pkb.getWriter());
  PKBReader& reader = pkb.getReader();

  vector<string> procs = {"Init", "Process", "Clean", "Finish", "Update"};
  ProcToVarSetMap expectedModifiesMap = {{"Init", {"u", "h", "v", "j"}},
                                         {"Process", {"u", "v", "j"}},
                                         {"Clean", {"u"}},
                                         {"Finish", {"v", "j"}},
                                         {"Update", {"v"}}};
  ProcToVarSetMap expectedUsesMap = {
      {"Init",
       {"a", "b", "c", "d", "e", "f", "h", "p", "q", "r", "u", "v", "j"}},
      {"Process", {"a", "b", "c", "d", "f", "p", "q", "r", "u", "v", "j"}},
      {"Clean", {}},
      {"Finish", {"j"}},
      {"Update", {"v"}}};
  ProcToStmtProcSetMap expectedCallsMap = {
      {"Init", {{"4", "Process"}}},
      {"Process", {{"7", "Finish"}, {"8", "Clean"}, {"10", "Update"}}},
      {"Clean", {}},
      {"Finish", {}},
      {"Update", {}}};
  ProcToStmtProcSetMap expectedCallsStarMap = {
      {"Init",
       {{"4", "Process"}, {"7", "Finish"}, {"8", "Clean"}, {"10", "Update"}}},
      {"Process", {{"7", "Finish"}, {"8", "Clean"}, {"10", "Update"}}},
      {"Clean", {}},
      {"Finish", {}},
      {"Update", {}}};
  validateUsesProcVar(reader, procs, expectedUsesMap);
  validateModifiesProcVar(reader, procs, expectedModifiesMap);
  validateCalls(reader, procs, expectedCallsMap);
  validateCallsStar(reader, procs, expectedCallsStarMap);
}
