#include <catch.hpp>

#include "../../utils/HelperFunctions.h"
#include "common/AliasTypes.h"
#include "pkb/facade/PKB.h"
#include "pkb/facade/PKBReader.h"
#include "sp/SourceProcessor.h"

using std::set, std::string, std::unordered_map, std::unordered_set;

using ProcToStrSetMap = unordered_map<string, unordered_set<string>>;

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
  StrStrPairVec expectedModifiesPairs = {{"1", "num1"}, {"3", "x"}};
  StrStrPairVec expectedUsesPairs = {{"2", "num2"}, {"3", "num1"}};
  REQUIRE(HelperFunctions::validateUses(reader, expectedUsesPairs));
  REQUIRE(HelperFunctions::validateModifies(reader, expectedModifiesPairs));
  REQUIRE(HelperFunctions::validateUsesProcVar(reader, procs, expectedUsesMap));
  REQUIRE(HelperFunctions::validateModifiesProcVar(reader, procs,
                                                   expectedModifiesMap));
  REQUIRE(HelperFunctions::validateCalls(reader, procs, expectedCallsMap));
  REQUIRE(HelperFunctions::validateCallsT(reader, procs, expectedCallsStarMap));
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
  StrStrPairVec expectedModifiesPairs = {
      {"2", "x"}, {"4", "y"}, {"3", "y"}, {"1", "x"}, {"1", "y"}};
  StrStrPairVec expectedUsesPairs = {
      {"2", "a"}, {"4", "b"}, {"3", "b"}, {"1", "a"}, {"1", "b"}};
  REQUIRE(HelperFunctions::validateUses(reader, expectedUsesPairs));
  REQUIRE(HelperFunctions::validateModifies(reader, expectedModifiesPairs));
  REQUIRE(HelperFunctions::validateUsesProcVar(reader, procs, expectedUsesMap));
  REQUIRE(HelperFunctions::validateModifiesProcVar(reader, procs,
                                                   expectedModifiesMap));
  REQUIRE(HelperFunctions::validateCalls(reader, procs, expectedCallsMap));
  REQUIRE(HelperFunctions::validateCallsT(reader, procs, expectedCallsStarMap));
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
      "procedure Z {"
      "print c;"  // 7
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
  StrStrPairVec expectedModifiesPairs = {
      {"3", "a"}, {"6", "a"}, {"1", "a"}, {"2", "a"}, {"4", "a"}};
  StrStrPairVec expectedUsesPairs = {{"3", "b"}, {"6", "a"}, {"2", "a"},
                                     {"2", "b"}, {"2", "c"}, {"5", "c"},
                                     {"4", "a"}, {"4", "c"}, {"7", "c"}};
  REQUIRE(HelperFunctions::validateUses(reader, expectedUsesPairs));
  REQUIRE(HelperFunctions::validateModifies(reader, expectedModifiesPairs));
  REQUIRE(HelperFunctions::validateUsesProcVar(reader, procs, expectedUsesMap));
  REQUIRE(HelperFunctions::validateModifiesProcVar(reader, procs,
                                                   expectedModifiesMap));
  REQUIRE(HelperFunctions::validateCalls(reader, procs, expectedCallsMap));
  REQUIRE(HelperFunctions::validateCallsT(reader, procs, expectedCallsStarMap));
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
  StrStrPairVec expectedModifiesPairs = {
      {"4", "z"}, {"3", "y"}, {"2", "z"}, {"1", "y"}, {"1", "z"}};
  StrStrPairVec expectedUsesPairs = {{"4", "x"}, {"2", "x"}, {"1", "x"}};
  REQUIRE(HelperFunctions::validateUses(reader, expectedUsesPairs));
  REQUIRE(HelperFunctions::validateModifies(reader, expectedModifiesPairs));
  REQUIRE(HelperFunctions::validateUsesProcVar(reader, procs, expectedUsesMap));
  REQUIRE(HelperFunctions::validateModifiesProcVar(reader, procs,
                                                   expectedModifiesMap));
  REQUIRE(HelperFunctions::validateCalls(reader, procs, expectedCallsMap));
  REQUIRE(HelperFunctions::validateCallsT(reader, procs, expectedCallsStarMap));
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
  StrStrPairVec expectedModifiesPairs = {
      {"2", "z"}, {"5", "z"}, {"3", "z"}, {"1", "z"}, {"4", "z"}};
  StrStrPairVec expectedUsesPairs = {{"2", "y"}, {"5", "z"}, {"4", "z"},
                                     {"3", "z"}, {"1", "z"}, {"1", "y"}};
  REQUIRE(HelperFunctions::validateUses(reader, expectedUsesPairs));
  REQUIRE(HelperFunctions::validateModifies(reader, expectedModifiesPairs));
  REQUIRE(HelperFunctions::validateUsesProcVar(reader, procs, expectedUsesMap));
  REQUIRE(HelperFunctions::validateModifiesProcVar(reader, procs,
                                                   expectedModifiesMap));
  REQUIRE(HelperFunctions::validateCalls(reader, procs, expectedCallsMap));
  REQUIRE(HelperFunctions::validateCallsT(reader, procs, expectedCallsStarMap));
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
  StrStrPairVec expectedModifiesPairs = {
      {"3", "b"}, {"4", "g"}, {"1", "b"}, {"2", "g"}};
  StrStrPairVec expectedUsesPairs = {
      {"3", "y"}, {"4", "z"}, {"1", "y"}, {"2", "z"}};
  REQUIRE(HelperFunctions::validateUses(reader, expectedUsesPairs));
  REQUIRE(HelperFunctions::validateModifies(reader, expectedModifiesPairs));
  REQUIRE(HelperFunctions::validateUsesProcVar(reader, procs, expectedUsesMap));
  REQUIRE(HelperFunctions::validateModifiesProcVar(reader, procs,
                                                   expectedModifiesMap));
  REQUIRE(HelperFunctions::validateCalls(reader, procs, expectedCallsMap));
  REQUIRE(HelperFunctions::validateCallsT(reader, procs, expectedCallsStarMap));
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
      "   } else {"
      "       a = a - 1; }"  // 8
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
  StrStrPairVec expectedModifiesPairs = {{"1", "a"}, {"3", "b"}, {"2", "b"},
                                         {"7", "a"}, {"6", "a"}, {"8", "a"},
                                         {"4", "a"}, {"2", "a"}};
  StrStrPairVec expectedUsesPairs = {
      {"2", "a"}, {"3", "a"}, {"5", "b"}, {"6", "b"}, {"6", "a"},
      {"7", "a"}, {"4", "a"}, {"4", "b"}, {"2", "b"}, {"8", "a"}};
  REQUIRE(HelperFunctions::validateUses(reader, expectedUsesPairs));
  REQUIRE(HelperFunctions::validateModifies(reader, expectedModifiesPairs));
  REQUIRE(HelperFunctions::validateUsesProcVar(reader, procs, expectedUsesMap));
  REQUIRE(HelperFunctions::validateModifiesProcVar(reader, procs,
                                                   expectedModifiesMap));
  REQUIRE(HelperFunctions::validateCalls(reader, procs, expectedCallsMap));
  REQUIRE(HelperFunctions::validateCallsT(reader, procs, expectedCallsStarMap));
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
  StrStrPairVec expectedModifiesPairs = {{"1", "k"}, {"2", "i"}, {"3", "i"},
                                         {"4", "i"}, {"5", "i"}, {"6", "i"}};
  StrStrPairVec expectedUsesPairs = {
      {"2", "a"}, {"2", "b"}, {"2", "c"}, {"2", "d"},

      {"3", "p"}, {"3", "q"}, {"3", "x"}, {"3", "y"}, {"3", "i"}, {"3", "j"},
      {"3", "k"},

      {"4", "p"}, {"4", "q"}, {"4", "x"}, {"4", "y"}, {"4", "i"}, {"4", "j"},
      {"4", "k"},

      {"5", "i"}, {"5", "j"}, {"5", "k"}, {"6", "i"}, {"6", "j"}, {"6", "k"}};
  REQUIRE(HelperFunctions::validateUses(reader, expectedUsesPairs));
  REQUIRE(HelperFunctions::validateModifies(reader, expectedModifiesPairs));
  REQUIRE(HelperFunctions::validateUsesProcVar(reader, procs, expectedUsesMap));
  REQUIRE(HelperFunctions::validateModifiesProcVar(reader, procs,
                                                   expectedModifiesMap));
  REQUIRE(HelperFunctions::validateCalls(reader, procs, expectedCallsMap));
  REQUIRE(HelperFunctions::validateCallsT(reader, procs, expectedCallsStarMap));
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
  StrStrPairVec expectedModifiesPairs = {
      {"1", "w"},  {"2", "m"},  {"3", "n"},  {"3", "o"},  {"3", "p"},
      {"3", "q"},  {"3", "r"},  {"3", "s"},  {"3", "t"},  {"4", "n"},
      {"4", "o"},  {"4", "p"},  {"4", "q"},  {"4", "r"},  {"4", "s"},
      {"4", "t"},  {"5", "n"},  {"6", "o"},  {"6", "q"},  {"6", "r"},
      {"6", "s"},  {"6", "t"},  {"7", "p"},  {"8", "n"},  {"10", "o"},
      {"11", "q"}, {"11", "r"}, {"11", "s"}, {"11", "t"}, {"12", "p"},
      {"13", "q"}, {"14", "r"}, {"15", "s"}, {"15", "t"}, {"17", "s"},
      {"17", "t"}, {"18", "s"}, {"19", "t"}};
  StrStrPairVec expectedUsesPairs = {
      {"2", "w"},  {"3", "m"},  {"3", "n"},  {"3", "o"},  {"3", "q"},
      {"3", "r"},  {"3", "s"},  {"4", "m"},  {"4", "n"},  {"4", "o"},
      {"4", "q"},  {"4", "r"},  {"4", "s"},  {"5", "m"},  {"6", "n"},
      {"6", "o"},  {"6", "q"},  {"6", "r"},  {"6", "s"},  {"7", "n"},
      {"8", "m"},  {"9", "n"},  {"10", "n"}, {"11", "o"}, {"11", "q"},
      {"11", "r"}, {"11", "s"}, {"12", "n"}, {"14", "o"}, {"14", "q"},
      {"15", "r"}, {"15", "s"}, {"16", "r"}, {"17", "r"}, {"17", "s"},
      {"19", "r"}, {"19", "s"}};
  REQUIRE(HelperFunctions::validateUses(reader, expectedUsesPairs));
  REQUIRE(HelperFunctions::validateModifies(reader, expectedModifiesPairs));
  REQUIRE(HelperFunctions::validateUsesProcVar(reader, procs, expectedUsesMap));
  REQUIRE(HelperFunctions::validateModifiesProcVar(reader, procs,
                                                   expectedModifiesMap));
  REQUIRE(HelperFunctions::validateCalls(reader, procs, expectedCallsMap));
  REQUIRE(HelperFunctions::validateCallsT(reader, procs, expectedCallsStarMap));
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
  StrStrPairVec expectedModifiesPairs = {
      {"1", "h"}, {"2", "u"},  {"3", "u"},  {"3", "j"},  {"3", "v"},
      {"4", "u"}, {"4", "j"},  {"4", "v"},  {"5", "u"},  {"6", "u"},
      {"6", "j"}, {"6", "v"},  {"7", "j"},  {"7", "v"},  {"8", "u"},
      {"9", "v"}, {"10", "v"}, {"12", "u"}, {"13", "j"}, {"14", "v"},
      {"15", "v"}};
  StrStrPairVec expectedUsesPairs = {
      {"2", "h"},  {"3", "a"}, {"3", "b"}, {"3", "c"},  {"3", "d"},
      {"3", "e"},  {"3", "f"}, {"3", "p"}, {"3", "q"},  {"3", "r"},
      {"3", "u"},  {"3", "v"}, {"3", "j"}, {"4", "a"},  {"4", "b"},
      {"4", "c"},  {"4", "d"}, {"4", "f"}, {"4", "p"},  {"4", "q"},
      {"4", "r"},  {"4", "u"}, {"4", "v"}, {"4", "j"},  {"5", "u"},
      {"6", "a"},  {"6", "b"}, {"6", "c"}, {"6", "d"},  {"6", "f"},
      {"6", "p"},  {"6", "q"}, {"6", "r"}, {"6", "j"},  {"6", "u"},
      {"6", "v"},  {"7", "j"}, {"9", "u"}, {"10", "v"}, {"11", "v"},
      {"14", "j"}, {"15", "v"}};
  REQUIRE(HelperFunctions::validateUses(reader, expectedUsesPairs));
  REQUIRE(HelperFunctions::validateModifies(reader, expectedModifiesPairs));
  REQUIRE(HelperFunctions::validateUsesProcVar(reader, procs, expectedUsesMap));
  REQUIRE(HelperFunctions::validateModifiesProcVar(reader, procs,
                                                   expectedModifiesMap));
  REQUIRE(HelperFunctions::validateCalls(reader, procs, expectedCallsMap));
  REQUIRE(HelperFunctions::validateCallsT(reader, procs, expectedCallsStarMap));
}
