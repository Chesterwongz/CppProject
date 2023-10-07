// TEMP_CATCH_INCLUDE
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../mocks/MockCFG.h"
#include "ExtractorUtils.h"
#include "sp/ast/ProgramNode.h"

using std::unique_ptr, std::make_unique, std::vector, std::string,
    std::unordered_map, std::unordered_set;

TEST_CASE("CFGExtractor - 1 procedure with 1 read") {
  string input =
      "procedure simple {"
      "read num1;"
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {1}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("simple",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - 1 procedure with different non-nesting statements") {
  string input =
      "procedure simple {"
      "read num1;"
      "print num1;"
      "x = 1;"
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2}}, {2, {3}}, {3, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {3}}, {3, {2}}, {2, {1}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("simple",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - 1 procedure with a while loop") {
  string input =
      "procedure simpleLoop {"
      "   read m;"          // 1
      "   while (m < 5) {"  // 2
      "       print m;"     // 3
      "       read n;"      // 4
      "   }"
      "   print n;"  // 5
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2}},
      {2, {3, 5}},
      {3, {4}},
      {4, {2}},
      {5, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {5}},
      {5, {2}},
      {4, {3}},
      {3, {2}},
      {2, {1, 4}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("simpleLoop",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - 1 procedure with an if statement") {
  string input =
      "procedure simpleIf {"
      "   read m;"            // 1
      "   if (m < 5) then {"  // 2
      "       x = m + 1;"     // 3
      "   } else {"
      "       y = 1;"  // 4
      "   }"
      "   print m;"  // 5
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2}},
      {2, {3, 4}},
      {3, {5}},
      {4, {5}},
      {5, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReverseCfg = {
      {common::CFG_END_STMT_NUM, {5}},
      {5, {4, 3}},
      {4, {2}},
      {3, {2}},
      {2, {1}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("simpleIf",
                   std::make_unique<MockCFG>(expectedCfg, expectedReverseCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - 1 procedure with multiple statements in if") {
  string input =
      "procedure multiStmts {"
      "   read h;"             // 1
      "   if (h == 0) then {"  // 2
      "       read i;"         // 3
      "       i = i + 1;"      // 4
      "       j = 0;"          // 5
      "   } else {"
      "       k = 1;"      // 6
      "       print k;"    // 7
      "       y = i + k;"  // 8
      "   }"
      "   print l;"  // 9
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2}}, {2, {3, 6}}, {3, {4}},
      {4, {5}}, {5, {9}},    {6, {7}},
      {7, {8}}, {8, {9}},    {9, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {9}},
      {9, {8, 5}},
      {8, {7}},
      {7, {6}},
      {6, {2}},
      {5, {4}},
      {4, {3}},
      {3, {2}},
      {2, {1}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("multiStmts",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - 1 procedure with nested if statements") {
  string input =
      "procedure multipleIf {"
      "   read v;"                          // 1
      "   read w;"                          // 2
      "   if (v == 0) then {"               // 3
      "       read x;"                      // 4
      "       if (w != v) then {"           // 5
      "           read y;"                  // 6
      "           if (x > (y - 1)) then {"  // 7
      "               read z;"              // 8
      "           } else { x = 1; }"        // 9
      "       } else { z = x + 1; }"        // 10
      "   } else { v = z; }"                // 11
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2}},
      {2, {3}},
      {3, {4, 11}},
      {4, {5}},
      {5, {6, 10}},
      {6, {7}},
      {7, {8, 9}},
      {8, {common::CFG_END_STMT_NUM}},
      {9, {common::CFG_END_STMT_NUM}},
      {10, {common::CFG_END_STMT_NUM}},
      {11, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {11, 9, 8, 10}},
      {11, {3}},
      {10, {5}},
      {9, {7}},
      {8, {7}},
      {7, {6}},
      {6, {5}},
      {5, {4}},
      {4, {3}},
      {3, {2}},
      {2, {1}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("multipleIf",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - 1 procedure with nested while statements") {
  string input =
      "procedure nestedWhile {"
      "   read v;"               // 1
      "   while (v > 0) {"       // 2
      "       read x;"           // 3
      "       while (x != v) {"  // 4
      "           y = 123;"      // 5
      "           print y;"      // 6
      "       }"
      "       x = y + 1;"  // 7
      "   }"
      "   print v;"  // 8
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2}}, {2, {3, 8}}, {3, {4}}, {4, {5, 7}},
      {5, {6}}, {6, {4}},    {7, {2}}, {8, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {8}},
      {8, {2}},
      {7, {4}},
      {6, {5}},
      {5, {4}},
      {4, {3, 6}},
      {3, {2}},
      {2, {1, 7}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("nestedWhile",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - 1 procedure with if in while statement") {
  string input =
      "procedure ifInWhile {"
      "   read v;"                  // 1
      "   while (v > 0) {"          // 2
      "       x = 1 + v;"           // 3
      "       if (x != v) then {"   // 4
      "           read y;"          // 5
      "           y = x + 2;"       // 6
      "       } else { print x; }"  // 7
      "   }"
      "   print v;"  // 8
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2}}, {2, {3, 8}}, {3, {4}}, {4, {5, 7}},
      {5, {6}}, {6, {2}},    {7, {2}}, {8, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {8}},
      {8, {2}},
      {7, {4}},
      {6, {5}},
      {5, {4}},
      {4, {3}},
      {3, {2}},
      {2, {1, 7, 6}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("ifInWhile",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - 1 procedure with while in if statement") {
  string input =
      "procedure whileInIf {"
      "   read a;"               // 1
      "   if (a == 1) then {"    // 2
      "       read b;"           // 3
      "       while (b < 10) {"  // 4
      "           read c;"       // 5
      "           c = c + 1;"    // 6
      "       }"
      "   } else { a = 342; }"  // 7
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2}},
      {2, {3, 7}},
      {3, {4}},
      {4, {5, common::CFG_END_STMT_NUM}},
      {5, {6}},
      {6, {4}},
      {7, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {7, 4}},
      {7, {2}},
      {6, {5}},
      {5, {4}},
      {4, {3, 6}},
      {3, {2}},
      {2, {1}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("whileInIf",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - multiple procedures") {
  string input =
      "procedure first {"
      "   read d;"            // 1
      "   if (d > 5) then {"  // 2
      "       call second;"   // 3
      "   } else { e = 1; }"  // 4
      "}"
      "procedure second {"
      "   read f;"           // 5
      "   while (f != 0) {"  // 6
      "       f = 0;"        // 7
      "       print g;"      // 8
      "   }"
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfgFirst = {
      {1, {2}},
      {2, {3, 4}},
      {3, {common::CFG_END_STMT_NUM}},
      {4, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfgFirst = {
      {common::CFG_END_STMT_NUM, {4, 3}}, {4, {2}}, {3, {2}}, {2, {1}}};
  unordered_map<int, unordered_set<int>> expectedCfgSecond = {
      {5, {6}},
      {6, {7, common::CFG_END_STMT_NUM}},
      {7, {8}},
      {8, {6}},
  };
  unordered_map<int, unordered_set<int>> expectedReversedCfgSecond = {
      {common::CFG_END_STMT_NUM, {6}}, {8, {7}}, {7, {6}}, {6, {5, 8}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("first", std::make_unique<MockCFG>(
                                expectedCfgFirst, expectedReversedCfgFirst));
  expected.emplace("second", std::make_unique<MockCFG>(
                                 expectedCfgSecond, expectedReversedCfgSecond));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - multiple nesting with while-if-while") {
  string input =
      "procedure multipleNesting {"
      "  while (x > 1) {"        // 1
      "    if (y != 2) then {"   // 2
      "       while (z <= 1) {"  // 3
      "           abc = xyz;"    // 4
      "       }"
      "       qwe = 1234;"  // 5
      "    } else {"
      "      while (while > 1) {"  // 6
      "        x = qwe;"           // 7
      "      }"
      "    }"
      "    read y;"  // 8
      "  }"
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2, common::CFG_END_STMT_NUM}},
      {2, {3, 6}},
      {3, {4, 5}},
      {4, {3}},
      {5, {8}},
      {6, {7, 8}},
      {7, {6}},
      {8, {1}},
  };
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {1}},
      {8, {6, 5}},
      {7, {6}},
      {6, {2, 7}},
      {5, {3}},
      {4, {3}},
      {3, {2, 4}},
      {2, {1}},
      {1, {8}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("multipleNesting",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - multiple nesting with while-if-if") {
  string input =
      "procedure nestedIfInWhile {"
      "  while (x > 1) {"          // 1
      "    if (y != 2) then {"     // 2
      "       if (z <= 1) then {"  // 3
      "           abc = xyz;"      // 4
      "       } else {"
      "           qwe = 1234;"  // 5
      "       }"
      "    } else {"
      "       if (w == 3) then {"  // 6
      "           x = qwe;"        // 7
      "       } else {"
      "           rty = 5678;"  // 8
      "       }"
      "    }"
      "    read y;"  // 9
      "  }"
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2, common::CFG_END_STMT_NUM}},
      {2, {3, 6}},
      {3, {4, 5}},
      {4, {9}},
      {5, {9}},
      {6, {7, 8}},
      {7, {9}},
      {8, {9}},
      {9, {1}},
  };
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {1}},
      {9, {7, 8, 4, 5}},
      {8, {6}},
      {7, {6}},
      {6, {2}},
      {5, {3}},
      {4, {3}},
      {3, {2}},
      {2, {1}},
      {1, {9}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("nestedIfInWhile",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - multiple nesting with if-if-while") {
  string input =
      "procedure nestedWhileInIf {"
      "  if (x > 1) then {"      // 1
      "    if (y != 2) then {"   // 2
      "       while (z <= 1) {"  // 3
      "           abc = xyz;"    // 4
      "       }"
      "       qwe = 1234;"  // 5
      "    } else {"
      "       while (w == 3) {"  // 6
      "           x = qwe;"      // 7
      "       }"
      "    }"
      "    read y;"  // 8
      "  } else {"
      "    print z;"  // 9
      "  }"
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2, 9}},
      {2, {3, 6}},
      {3, {4, 5}},
      {4, {3}},
      {5, {8}},
      {6, {7, 8}},
      {7, {6}},
      {8, {common::CFG_END_STMT_NUM}},
      {9, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {9, 8}},
      {9, {1}},
      {8, {6, 5}},
      {7, {6}},
      {6, {2, 7}},
      {5, {3}},
      {4, {3}},
      {3, {2, 4}},
      {2, {1}},
  };
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("nestedWhileInIf",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - multiple nesting with while-while-if") {
  string input =
      "procedure nestedIfInDoubleWhile {"
      "  while (x > 1) {"          // 1
      "    while (y != 2) {"       // 2
      "       if (z <= 1) then {"  // 3
      "           abc = xyz;"      // 4
      "       } else {"
      "           qwe = 1234;"  // 5
      "       }"
      "    }"
      "    read y;"  // 6
      "  }"
      "  print x;"  // 7
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2, 7}},
      {2, {3, 6}},
      {3, {4, 5}},
      {4, {2}},
      {5, {2}},
      {6, {1}},
      {7, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {7}},
      {7, {1}},
      {6, {2}},
      {5, {3}},
      {4, {3}},
      {3, {2}},
      {2, {1, 5, 4}},
      {1, {6}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("nestedIfInDoubleWhile",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - multiple nesting with if-if-if") {
  string input =
      "procedure tripleNestedIf {"
      "  if (x > 1) then {"        // 1
      "    if (y != 2) then {"     // 2
      "       if (z <= 1) then {"  // 3
      "           abc = xyz;"      // 4
      "       } else {"
      "           qwe = 1234;"  // 5
      "       }"
      "    } else {"
      "       print w;"  // 6
      "    }"
      "    read y;"  // 7
      "  } else {"
      "    print z;"  // 8
      "  }"
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2, 8}},
      {2, {3, 6}},
      {3, {4, 5}},
      {4, {7}},
      {5, {7}},
      {6, {7}},
      {7, {common::CFG_END_STMT_NUM}},
      {8, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {8, 7}},
      {8, {1}},
      {7, {6, 4, 5}},
      {6, {2}},
      {5, {3}},
      {4, {3}},
      {3, {2}},
      {2, {1}},
  };
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("tripleNestedIf",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - multiple nesting with while-while-while") {
  string input =
      "procedure tripleNestedWhile {"
      "  while (x > 1) {"        // 1
      "    while (y != 2) {"     // 2
      "       while (z <= 1) {"  // 3
      "           abc = xyz;"    // 4
      "       }"
      "       qwe = 1234;"  // 5
      "    }"
      "    read y;"  // 6
      "  }"
      "  print x;"  // 7
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2, 7}},
      {2, {3, 6}},
      {3, {4, 5}},
      {4, {3}},
      {5, {2}},
      {6, {1}},
      {7, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {7}},
      {7, {1}},
      {6, {2}},
      {5, {3}},
      {4, {3}},
      {3, {2, 4}},
      {2, {1, 5}},
      {1, {6}}};
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("tripleNestedWhile",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - multiple nesting with if-while-while") {
  string input =
      "procedure doubleNestedWhileInIf {"
      "  if (x > 1) then {"      // 1
      "    while (y != 2) {"     // 2
      "       while (z <= 1) {"  // 3
      "           abc = xyz;"    // 4
      "       }"
      "       qwe = 1234;"  // 5
      "    }"
      "    read y;"  // 6
      "  } else {"
      "    print z;"  // 7
      "  }"
      "}";
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfg = {
      {1, {2, 7}},
      {2, {3, 6}},
      {3, {4, 5}},
      {4, {3}},
      {5, {2}},
      {6, {common::CFG_END_STMT_NUM}},
      {7, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfg = {
      {common::CFG_END_STMT_NUM, {7, 6}},
      {7, {1}},
      {6, {2}},
      {5, {3}},
      {4, {3}},
      {3, {2, 4}},
      {2, {1, 5}},
  };
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("doubleNestedWhileInIf",
                   std::make_unique<MockCFG>(expectedCfg, expectedReversedCfg));
  REQUIRE(mockPKB.isCFGEqual(expected));
}

TEST_CASE("CFGExtractor - wiki code 6") {
  string input =
      "procedure Second {"
      "    x = 0;"            // 1
      "    i = 5;"            // 2
      "    while (i!=0) {"    // 3
      "        x = x + 2*y;"  // 4
      "        call Third;"   // 5
      "        i = i - 1; "   // 6
      "    }"
      "    if (x==1) then {"        // 7
      "        x = x+1; }"          // 8
      "    else { z = 1; }"         // 9
      "    z= z + x + i; "          // 10
      "    y= z + 2;"               // 11
      "    x= x * y + z; }"         // 12
      "procedure Third {read x;}";  // 13
  // extract
  PKBStorage storage{};
  MockPKBWriter mockPKB(storage);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  unordered_map<int, unordered_set<int>> expectedCfgSecond = {
      {1, {2}},  {2, {3}},   {3, {4, 7}}, {4, {5}},
      {5, {6}},  {6, {3}},   {7, {8, 9}}, {8, {10}},
      {9, {10}}, {10, {11}}, {11, {12}},  {12, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfgSecond = {
      {common::CFG_END_STMT_NUM, {12}},
      {12, {11}},
      {11, {10}},
      {10, {9, 8}},
      {9, {7}},
      {8, {7}},
      {7, {3}},
      {6, {5}},
      {5, {4}},
      {4, {3}},
      {3, {2, 6}},
      {2, {1}},
  };
  unordered_map<int, unordered_set<int>> expectedCfgThird = {
      {13, {common::CFG_END_STMT_NUM}}};
  unordered_map<int, unordered_set<int>> expectedReversedCfgThird = {
      {common::CFG_END_STMT_NUM, {13}},
  };
  unordered_map<string, unique_ptr<CFG>> expected;
  expected.emplace("Second", std::make_unique<MockCFG>(
                                 expectedCfgSecond, expectedReversedCfgSecond));
  expected.emplace("Third", std::make_unique<MockCFG>(
                                expectedCfgThird, expectedReversedCfgThird));
  REQUIRE(mockPKB.isCFGEqual(expected));
}
