#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <catch.hpp>

#include "pkb/facade/PKB.h"
#include "pkb/facade/PKBReader.h"
#include "sp/SourceProcessor.h"

using std::set, std::string, std::unordered_map, std::unordered_set;

using ProcToStrSetMap = unordered_map<string, unordered_set<string>>;

// TODO(Xiaoyun): remove print methods after MS2 testing
void printEntities(const string& abstraction,
                   const unordered_set<string>& set) {
  std::cout << abstraction << ": ";
  for (const string& entity : set) {
    std::cout << entity << ", ";
  }
  std::cout << std::endl << "-------------" << std::endl;
}

void validateModifiesProcVar(PKBReader& reader, const vector<string>& procs,
                             ProcToStrSetMap expectedModifiesMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedModifies = expectedModifiesMap[proc];
    unordered_set<string> actualModifies =
        reader.getModifiedVariablesForProc(proc);
    REQUIRE(actualModifies == expectedModifies);
  }
}

void validateUsesProcVar(PKBReader& reader, const vector<string>& procs,
                         ProcToStrSetMap expectedUsesMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedUses = expectedUsesMap[proc];
    unordered_set<string> actualUses = reader.getUsedVariablesForProc(proc);
    REQUIRE(actualUses == expectedUses);
  }
}

void validateCalls(PKBReader& reader, const vector<string>& procs,
                   ProcToStrSetMap expectedCallsMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedCalls = expectedCallsMap[proc];
    unordered_set<string> actualCalls = reader.getCalleeProcs(proc);
    REQUIRE(actualCalls == expectedCalls);
  }
}

void validateCallsStar(PKBReader& reader, const vector<string>& procs,
                       ProcToStrSetMap expectedCallsStarMap) {
  for (const string& proc : procs) {
    unordered_set<string> expectedCallsStar = expectedCallsStarMap[proc];
    unordered_set<string> actualCallsStar = reader.getCalleeProcsStar(proc);
    REQUIRE(actualCallsStar == expectedCallsStar);
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
  ProcToStrSetMap expectedModifiesMap = {{"simple", {"num1", "x"}}};
  ProcToStrSetMap expectedUsesMap = {{"simple", {"num1", "num2"}}};
  ProcToStrSetMap expectedCallsMap = {{"simple", {}}};
  ProcToStrSetMap expectedCallsStarMap = {{"simple", {}}};
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
  ProcToStrSetMap expectedModifiesMap = {
      {"A", {"x", "y"}}, {"B", {"x", "y"}}, {"C", {"y"}}};
  ProcToStrSetMap expectedUsesMap = {
      {"A", {"a", "b"}}, {"B", {"a", "b"}}, {"C", {"b"}}};
  ProcToStrSetMap expectedCallsMap = {{"A", {"B"}}, {"B", {"C"}}, {"C", {}}};
  ProcToStrSetMap expectedCallsStarMap = {
      {"A", {"B", "C"}}, {"B", {"C"}}, {"C", {}}};
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
  ProcToStrSetMap expectedModifiesMap = {{"X", {"a"}}, {"Y", {"a"}}};
  ProcToStrSetMap expectedUsesMap = {
      {"X", {"a", "b", "c"}}, {"Y", {"a", "b", "c"}}, {"Z", {"c"}}};
  ProcToStrSetMap expectedCallsMap = {{"X", {"Y"}}, {"Y", {"Z"}}, {"Z", {}}};
  ProcToStrSetMap expectedCallsStarMap = {
      {"X", {"Y", "Z"}}, {"Y", {"Z"}}, {"Z", {}}};
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
  ProcToStrSetMap expectedModifiesMap = {{"A", {"y", "z"}}, {"B", {"z"}}};
  ProcToStrSetMap expectedUsesMap = {{"A", {"x"}}, {"B", {"x"}}};
  ProcToStrSetMap expectedCallsMap = {{"A", {"B"}}, {"B", {}}};
  ProcToStrSetMap expectedCallsStarMap = {{"A", {"B"}}, {"B", {}}};
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
  ProcToStrSetMap expectedModifiesMap = {
      {"P", {"z"}}, {"Q", {"z"}}, {"R", {"z"}}, {"S", {"z"}}};
  ProcToStrSetMap expectedUsesMap = {
      {"P", {"z", "y"}}, {"Q", {"z", "y"}}, {"R", {"z"}}, {"S", {"z"}}};
  ProcToStrSetMap expectedCallsMap = {
      {"P", {"Q"}}, {"Q", {"R"}}, {"R", {"S"}}, {"S", {}}};
  ProcToStrSetMap expectedCallsStarMap = {
      {"P", {"Q", "R", "S"}}, {"Q", {"R", "S"}}, {"R", {"S"}}, {"S", {}}};
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
  ProcToStrSetMap expectedModifiesMap = {
      {"Alpha", {"b", "g"}}, {"Beta", {"b"}}, {"Gamma", {"g"}}};
  ProcToStrSetMap expectedUsesMap = {
      {"Alpha", {"y", "z"}}, {"Beta", {"y"}}, {"Gamma", {"z"}}};
  ProcToStrSetMap expectedCallsMap = {
      {"Alpha", {"Beta", "Gamma"}}, {"Beta", {}}, {"Gamma", {}}};
  ProcToStrSetMap expectedCallsStarMap = {
      {"Alpha", {"Beta", "Gamma"}}, {"Beta", {}}, {"Gamma", {}}};
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
  ProcToStrSetMap expectedModifiesMap = {{"Main", {"a", "b"}},
                                         {"Helper", {"a"}}};
  ProcToStrSetMap expectedUsesMap = {{"Main", {"a", "b"}},
                                     {"Helper", {"a", "b"}}};
  ProcToStrSetMap expectedCallsMap = {{"Main", {"Helper"}}, {"Helper", {}}};
  ProcToStrSetMap expectedCallsStarMap = {{"Main", {"Helper"}}, {"Helper", {}}};
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
  ProcToStrSetMap expectedModifiesMap = {
      {"Start", {"i", "k"}}, {"Operate", {"i"}}, {"Increment", {"i"}}};
  ProcToStrSetMap expectedUsesMap = {
      {"Start", {"p", "q", "x", "y", "i", "j", "k", "a", "b", "c", "d"}},
      {"Operate", {"p", "q", "x", "y", "i", "j", "k"}},
      {"Increment", {"i", "j", "k"}}};
  ProcToStrSetMap expectedCallsMap = {
      {"Start", {"Operate"}}, {"Operate", {"Increment"}}, {"Increment", {}}};
  ProcToStrSetMap expectedCallsStarMap = {{"Start", {"Operate", "Increment"}},
                                          {"Operate", {"Increment"}},
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
  ProcToStrSetMap expectedModifiesMap = {
      {"Alpha", {"w", "m", "n", "o", "q", "r", "s", "t", "p"}},
      {"Beta", {"n", "o", "q", "r", "s", "t", "p"}},
      {"Gamma", {"o", "q", "r", "s", "t"}},
      {"Delta", {"p"}},
      {"Epsilon", {"q", "r", "s", "t"}},
      {"Zeta", {"s", "t"}},
      {"Eta", {"s", "t"}}};
  ProcToStrSetMap expectedUsesMap = {
      {"Alpha", {"w", "o", "q", "r", "s", "m", "n"}},
      {"Beta", {"m", "n", "o", "q", "r", "s"}},
      {"Gamma", {"n", "o", "q", "r", "s"}},
      {"Delta", {"n"}},
      {"Epsilon", {"o", "q", "r", "s"}},
      {"Zeta", {"r", "s"}},
      {"Eta", {"r", "s"}}};
  ProcToStrSetMap expectedCallsMap = {
      {"Alpha", {"Beta"}}, {"Beta", {"Gamma", "Delta"}}, {"Gamma", {"Epsilon"}},
      {"Delta", {}},       {"Epsilon", {"Zeta"}},        {"Zeta", {"Eta"}},
      {"Eta", {}}};
  ProcToStrSetMap expectedCallsStarMap = {
      {"Alpha", {"Beta", "Gamma", "Delta", "Epsilon", "Zeta", "Eta"}},
      {"Beta", {"Gamma", "Delta", "Epsilon", "Zeta", "Eta"}},
      {"Gamma", {"Epsilon", "Zeta", "Eta"}},
      {"Delta", {}},
      {"Epsilon", {"Zeta", "Eta"}},
      {"Zeta", {"Eta"}},
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
  ProcToStrSetMap expectedModifiesMap = {{"Init", {"u", "h", "v", "j"}},
                                         {"Process", {"u", "v", "j"}},
                                         {"Clean", {"u"}},
                                         {"Finish", {"v", "j"}},
                                         {"Update", {"v"}}};
  ProcToStrSetMap expectedUsesMap = {
      {"Init",
       {"a", "b", "c", "d", "e", "f", "h", "p", "q", "r", "u", "v", "j"}},
      {"Process", {"a", "b", "c", "d", "f", "p", "q", "r", "u", "v", "j"}},
      {"Clean", {}},
      {"Finish", {"j"}},
      {"Update", {"v"}}};
  ProcToStrSetMap expectedCallsMap = {
      {"Init", {"Process"}},
      {"Process", {"Finish", "Clean", "Update"}},
      {"Clean", {}},
      {"Finish", {}},
      {"Update", {}}};
  ProcToStrSetMap expectedCallsStarMap = {
      {"Init", {"Process", "Finish", "Clean", "Update"}},
      {"Process", {"Finish", "Clean", "Update"}},
      {"Clean", {}},
      {"Finish", {}},
      {"Update", {}}};
  validateUsesProcVar(reader, procs, expectedUsesMap);
  validateModifiesProcVar(reader, procs, expectedModifiesMap);
  validateCalls(reader, procs, expectedCallsMap);
  validateCallsStar(reader, procs, expectedCallsStarMap);
}
