#include <catch.hpp>
#include <map>
#include <memory>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../ast/TNodeUtils.h"
#include "../mocks/MockData.h"
#include "../mocks/MockPKBWriter.h"
#include "AbstractionTypes.h"
#include "ExtractorUtils.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/StmtListNode.h"

using std::unique_ptr, std::make_unique, std::vector, std::string, std::map,
    std::set, std::unordered_map, std::unordered_set, std::pair;

TEST_CASE("PatternExtractor for assign - no assign pattern") {
  //    string input =
  //        "procedure simple {"
  //        "print x;"
  //        "}";
  unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
  unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
  unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
  stmtListNode->addChild(makePrintNode(1, "x"));
  procNode->addChild(std::move(stmtListNode));
  programNode->addChild(std::move(procNode));

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(*programNode, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, pair<string, string>> expected =
      unordered_map<int, pair<string, string>>();
  REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE("PatternExtractor for assign with parser - no assign pattern") {
  string input =
      "procedure simple {"
      "print x;"
      "}";
  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, pair<string, string>> expected =
      unordered_map<int, pair<string, string>>();
  REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE("PatternExtractor for assign - 2 simple assign patterns") {
  //    string input =
  //        "procedure simple {"
  //        "x = z + 2"
  //        "y = x + 1"
  //        "}";
  unique_ptr<ProgramNode> programNode = make_unique<ProgramNode>();
  unique_ptr<ProcNode> procNode = make_unique<ProcNode>("simple");
  unique_ptr<StmtListNode> stmtListNode = make_unique<StmtListNode>();
  stmtListNode->addChild(makeAssignWithPlusNode(1, "x", "z", "2"));
  stmtListNode->addChild(makeAssignWithPlusNode(2, "y", "x", "1"));
  procNode->addChild(std::move(stmtListNode));
  programNode->addChild(std::move(procNode));

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(*programNode, mockPKB, AbstractionType::PATTERN);

  unordered_map<int, pair<string, string>> expected = {};
  expected[1] = {"x", " z 2 + "};
  expected[2] = {"y", " x 1 + "};
  REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE(
    "PatternExtractor for assign with parser - 2 simple assign patterns") {
  string input =
      "procedure simple {"
      "x = z + 2;"
      "y = x + 1;"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);

  unordered_map<int, pair<string, string>> expected = {};
  expected[1] = {"x", " z 2 + "};
  expected[2] = {"y", " x 1 + "};
  REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE(
    "PatternExtractor for assign with parser - 2 same assign patterns for same "
    "var") {
  string input =
      "procedure simple {"
      "x = a - b * c;"
      "x = a - b * c;"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, pair<string, string>> expected = {};
  expected[1] = {"x", " a b c * - "};
  expected[2] = {"x", " a b c * - "};
  REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE(
    "PatternExtractor for assign with parser - 3 diff assign patterns for same "
    "var") {
  string input =
      "procedure simple {"
      "x = a - b * c;"
      "x = a * b + c;"
      "x = a / b - c * d;"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, pair<string, string>> expected = {};
  expected[1] = {"x", " a b c * - "};
  expected[2] = {"x", " a b * c + "};
  expected[3] = {"x", " a b / c d * - "};
  REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE(
    "PatternExtractor for assign with parser - diff assign pattern for diff "
    "vars with parentheses") {
  string input =
      "procedure simple {"
      "y = (a + b) * c;"
      "z = a * (b + c);"
      "x = (a + b) * (c - d);"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, pair<string, string>> expected = {};
  expected[1] = {"y", " a b + c * "};
  expected[2] = {"z", " a b c + * "};
  expected[3] = {"x", " a b + c d - * "};
  REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE("PatternExtractor for assign with parser - one container node") {
  string input =
      "procedure simple {"
      "read y;"
      "z = (a + b) * (c + d) - e / f * g;"
      "if (num1 < num2) then {"
      "x = a + b * c - d / e;"
      "} else {"
      "y = a * b + c / d;"
      "read z;"
      "}"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, pair<string, string>> expected = {};
  expected[2] = {"z", " a b + c d + * e f / g * - "};
  expected[4] = {"x", " a b c * + d e / - "};
  expected[5] = {"y", " a b * c d / + "};
  REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE("PatternExtractor for assign with parser - nested container node") {
  string input =
      "procedure simple {"
      "read x;"
      "y = a * b + c % d - e;"
      "while (x < y) {"
      "if (x == y) then {"
      "x = a + b * c % d - e;"
      "} else { w = (a + b) % c; }"
      "z = a % b + c % d;"
      "}"
      "num1 = (a + b * c) % d;"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, pair<string, string>> expected = {};
  expected[2] = {"y", " a b * c d % + e - "};
  expected[5] = {"x", " a b c * d % + e - "};
  expected[6] = {"w", " a b + c % "};
  expected[7] = {"z", " a b % c + c d % + "};
  expected[8] = {"num1", " a b c * + d % "};
}

TEST_CASE(
    "PatternExtractor for assign with parser - assign pattern with all "
    "operators") {
  string input =
      "procedure simple {"
      "read a; read b; read c; read d; read e; read f;"  // 1-6
      "x = a + b * c - d / e % f;"                       // 7
      "y = (a + b) * (c - d) / (e % f);"                 // 8
      "z = a * (b + c * d - e / f) % g;"                 // 9
      "a = a - b / c * d + e % f * g;"                   // 10
      "b = (a * b - c) % (d + e / f);"                   // 11
      "c = a / (b + c) * d - e % f + g;"                 // 12
      "d = a + b * (c % d - e) / f;"                     // 13
      "e = (a % b) * c - d / (e + f);"                   // 14
      "f = a / b * (c + d) % e - f;"                     // 115
      "g = (a + b % c) * (d - e / f);"                   // 16
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, pair<string, string>> expected = {};
  expected[7] = {"x", " a b c * + d e / f % - "};
  expected[8] = {"y", " a b + c d - * e f % / "};
  expected[9] = {"z", " a b c d * + e f / - * g % "};
  expected[10] = {"a", " a b c / d * - e f % g * + "};
  expected[11] = {"b", " a b * c - d e f / + % "};
  expected[12] = {"c", " a b c + / d * e f % - g + "};
  expected[13] = {"d", " a b c d % e - * f / + "};
  expected[14] = {"e", " a b % c * d e f + / - "};
  expected[15] = {"f", " a b / c d + * e % f - "};
  expected[16] = {"g", " a b c % + d e f / - * "};
  REQUIRE(mockPKB.isAssignPatternEqual(expected));
}

TEST_CASE("PatternExtractor for while with parser - no while patter") {
  string input =
      "procedure simple {"
      "print x;"
      "}";
  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, unordered_set<string>> expected = {};
  REQUIRE(mockPKB.isWhilePatternEqual(expected));
}

TEST_CASE("PatternExtractor for while with parser - 1 while pattern") {
  string input =
      "procedure simple {"
      "read x;"
      "while (x < y) {"
      "read y;"
      "}"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, unordered_set<string>> expected = {};
  expected[2] = {"x", "y"};
  REQUIRE(mockPKB.isWhilePatternEqual(expected));
}

TEST_CASE("PatternExtractor for while with parser - 2 nested while pattern") {
  string input =
      "procedure nestedWhile {"
      "   read a;"
      "   read b;"
      "   while (a == b) {"
      "       read c;"
      "       while (c != a) {"
      "           read d;"
      "       }"
      "   }"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, unordered_set<string>> expected = {};
  expected[3] = {"a", "b"};
  expected[5] = {"c", "a"};
  REQUIRE(mockPKB.isWhilePatternEqual(expected));
}

TEST_CASE("PatternExtractor for while with parser - 3 nested while pattern") {
  string input =
      "procedure multipleWhiles {"
      "   read v;"
      "   read w;"
      "   while (v == 0) {"
      "       read x;"
      "       while (w != v) {"
      "           read y;"
      "           while (x > (y - 1)) {"
      "               read z;"
      "           }"
      "       }"
      "   }"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, unordered_set<string>> expected = {};
  expected[3] = {"v"};
  expected[5] = {"w", "v"};
  expected[7] = {"x", "y"};
  REQUIRE(mockPKB.isWhilePatternEqual(expected));
}

TEST_CASE("PatternExtractor for while with parser - sequential while pattern") {
  string input =
      "procedure multipleWhile {"
      "   read i;"
      "   while (i > 0) {"
      "       read j;"
      "   }"
      "   read k;"
      "   while (k <= i) {"
      "       read l;"
      "   }"
      "}";
  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, unordered_set<string>> expected = {};
  expected[2] = {"i"};
  expected[5] = {"k", "i"};
  REQUIRE(mockPKB.isWhilePatternEqual(expected));
}

TEST_CASE(
    "PatternExtractor for while with parser - multiple control variables") {
  string input =
      "procedure complexConditions {"
      "   read p;"
      "   read q;"
      "   while ((p + q * 2) == (x - y % 3)) {"
      "       read r;"
      "   }"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, unordered_set<string>> expected = {};
  expected[3] = {"p", "q", "x", "y"};
  REQUIRE(mockPKB.isWhilePatternEqual(expected));
}

TEST_CASE("PatternExtractor for if with parser - no if patter") {
  string input =
      "procedure simple {"
      "print x;"
      "}";
  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, unordered_set<string>> expected = {};
  REQUIRE(mockPKB.isIfPatternEqual(expected));
}

TEST_CASE("PatternExtractor for if with parser - 1 if pattern") {
  string input =
      "procedure simple {"
      "read x;"
      "if (x < y) then {"
      "read y;"
      "} else { read z; }"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, unordered_set<string>> expected = {};
  expected[2] = {"x", "y"};
  REQUIRE(mockPKB.isIfPatternEqual(expected));
}

TEST_CASE("PatternExtractor for if with parser - 2 nested if pattern") {
  string input =
      "procedure nestedIf {"
      "   read a;"
      "   read b;"
      "   if (a == b) then {"
      "       read c;"
      "       if (c != a) then {"
      "           read d;"
      "       } else { print a; }"
      "   } else { print b; }"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, unordered_set<string>> expected = {};
  expected[3] = {"a", "b"};
  expected[5] = {"c", "a"};
  REQUIRE(mockPKB.isIfPatternEqual(expected));
}

TEST_CASE("PatternExtractor for if with parser - 3 nested if pattern") {
  string input =
      "procedure multipleIf {"
      "   read v;"
      "   read w;"
      "   if (v == 0) then {"
      "       read x;"
      "       if (w != v) then {"
      "           read y;"
      "           if (x > (y - 1)) then {"
      "               read z;"
      "           } else { print x; }"
      "       } else { print z; }"
      "   } else { print v; }"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, unordered_set<string>> expected = {};
  expected[3] = {"v"};
  expected[5] = {"w", "v"};
  expected[7] = {"x", "y"};
  REQUIRE(mockPKB.isIfPatternEqual(expected));
}

TEST_CASE("PatternExtractor for if with parser - sequential if pattern") {
  string input =
      "procedure multipleIf {"
      "   read i;"
      "   if (i > 0) then {"
      "       read j;"
      "   } else { read i; }"
      "   read k;"
      "   if (k <= i) then {"
      "       read l;"
      "   } else { print i; }"
      "}";
  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, unordered_set<string>> expected = {};
  expected[2] = {"i"};
  expected[6] = {"k", "i"};
  REQUIRE(mockPKB.isIfPatternEqual(expected));
}

TEST_CASE("PatternExtractor for if with parser - multiple control variables") {
  string input =
      "procedure complexConditions {"
      "   read p;"
      "   read q;"
      "   if ((p + q * 2) == (x - y % 3)) then {"
      "       read r;"
      "   } else { print p; }"
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, unordered_set<string>> expected = {};
  expected[3] = {"p", "q", "x", "y"};
  REQUIRE(mockPKB.isIfPatternEqual(expected));
}

TEST_CASE("PatternExtractor with all patterns") {
  string input =
      "procedure nestedWhile {"
      "    read a; read b; read c; read d; read e; read f;"  // 1-6
      "    x = a + b * c - d / e % f;"                       // 7
      "    while (a == b) {"                                 // 8
      "        y = (a + b) * (c - d) / (e % f);"             // 9
      "        if (c != a) then {"                           // 10
      "            z = a * (b + c * d - e / f) % g;"         // 11
      "        } else {"
      "            a = a - b / c * d + e % f * g;"  // 12
      "        }"
      "        while ((a + b * 2) == (x - y % 3)) {"  // 13
      "            b = (a * b - c) % (d + e / f);"    // 14
      "            c = a / (b + c) * d - e % f + g;"  // 15
      "        }"
      "    }"
      "    if ((c + d) > (e - f)) then {"         // 16
      "        while (a < b) {"                   // 17
      "            d = a + b * (c % d - e) / f;"  // 18
      "        }"
      "        e = (a % b) * c - d / (e + f);"  // 19
      "    } else {"
      "        f = a / b * (c + d) % e - f;"  // 20
      "    }"
      "    g = (a + b % c) * (d - e / f);"  // 21
      "}";

  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORAGE, MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::PATTERN);
  unordered_map<int, pair<string, string>> expectedAssignStorage = {};
  unordered_map<int, unordered_set<string>> expectedWhileStorage = {};
  unordered_map<int, unordered_set<string>> expectedIfStorage = {};
  expectedAssignStorage[7] = {"x", " a b c * + d e / f % - "};
  expectedAssignStorage[9] = {"y", " a b + c d - * e f % / "};
  expectedAssignStorage[11] = {"z", " a b c d * + e f / - * g % "};
  expectedAssignStorage[12] = {"a", " a b c / d * - e f % g * + "};
  expectedAssignStorage[14] = {"b", " a b * c - d e f / + % "};
  expectedAssignStorage[15] = {"c", " a b c + / d * e f % - g + "};
  expectedAssignStorage[18] = {"d", " a b c d % e - * f / + "};
  expectedAssignStorage[19] = {"e", " a b % c * d e f + / - "};
  expectedAssignStorage[20] = {"f", " a b / c d + * e % f - "};
  expectedAssignStorage[21] = {"g", " a b c % + d e f / - * "};
  expectedWhileStorage[8] = {"a", "b"};
  expectedWhileStorage[13] = {"a", "b", "x", "y"};
  expectedWhileStorage[17] = {"a", "b"};
  expectedIfStorage[10] = {"c", "a"};
  expectedIfStorage[16] = {"c", "d", "e", "f"};
  REQUIRE(mockPKB.isAssignPatternEqual(expectedAssignStorage));
  REQUIRE(mockPKB.isWhilePatternEqual(expectedWhileStorage));
  REQUIRE(mockPKB.isIfPatternEqual(expectedIfStorage));
}
