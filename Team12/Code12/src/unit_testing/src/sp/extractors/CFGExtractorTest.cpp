#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <catch.hpp>

#include "../mocks/MockData.h"
#include "ExtractorUtils.h"
#include "common/AliasTypes.h"

using std::unique_ptr, std::make_unique, std::vector, std::string,
    std::unordered_map, std::unordered_set;

TEST_CASE("CFGExtractor - 1 procedure with 1 read") {
  string input =
      "procedure simple {"
      "read num1;"
      "}";
  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  REQUIRE(mockPKB.isNextEqual({}));
}

TEST_CASE("CFGExtractor - 1 procedure with different non-nesting statements") {
  string input =
      "procedure simple {"
      "read num1;"
      "print num1;"
      "x = 1;"
      "}";
  // extract
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2}}, {2, {3}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2}}, {2, {3, 5}}, {3, {4}}, {4, {2}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2}}, {2, {3, 4}}, {3, {5}}, {4, {5}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2}}, {2, {3, 6}}, {3, {4}}, {4, {5}},
                                 {5, {9}}, {6, {7}},    {7, {8}}, {8, {9}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2}},     {2, {3}}, {3, {4, 11}}, {4, {5}},
                                 {5, {6, 10}}, {6, {7}}, {7, {8, 9}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2}}, {2, {3, 8}}, {3, {4}}, {4, {5, 7}},
                                 {5, {6}}, {6, {4}},    {7, {2}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2}}, {2, {3, 8}}, {3, {4}}, {4, {5, 7}},
                                 {5, {6}}, {6, {2}},    {7, {2}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2}}, {2, {3, 7}}, {3, {4}},
                                 {4, {5}}, {5, {6}},    {6, {4}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2}}, {2, {3, 4}}, {5, {6}},
                                 {6, {7}}, {7, {8}},    {8, {6}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2}}, {2, {3, 6}}, {3, {4, 5}}, {4, {3}},
                                 {5, {8}}, {6, {7, 8}}, {7, {6}},    {8, {1}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {
      {1, {2}},    {2, {3, 6}}, {3, {4, 5}}, {4, {9}}, {5, {9}},
      {6, {7, 8}}, {7, {9}},    {8, {9}},    {9, {1}},
  };
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2, 9}}, {2, {3, 6}}, {3, {4, 5}},
                                 {4, {3}},    {5, {8}},    {6, {7, 8}},
                                 {7, {6}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2, 7}}, {2, {3, 6}}, {3, {4, 5}},
                                 {4, {2}},    {5, {2}},    {6, {1}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2, 8}}, {2, {3, 6}}, {3, {4, 5}},
                                 {4, {7}},    {5, {7}},    {6, {7}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2, 7}}, {2, {3, 6}}, {3, {4, 5}},
                                 {4, {3}},    {5, {2}},    {6, {1}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {
      {1, {2, 7}}, {2, {3, 6}}, {3, {4, 5}}, {4, {3}}, {5, {2}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
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
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2}},  {2, {3}},   {3, {4, 7}}, {4, {5}},
                                 {5, {6}},  {6, {3}},   {7, {8, 9}}, {8, {10}},
                                 {9, {10}}, {10, {11}}, {11, {12}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
}

TEST_CASE("CFGExtractor - integration test") {
  string input =
      "procedure Next {"
      "  read line1;"                                    // 1
      "  if (line2 > line2)then {"                       // 2
      "    while((line3 < line3)&& ( line3 == line3)){"  // 3
      "      print line4;"                               // 4
      "    }"
      "    call Potato;"  // 5
      "  } else {"
      "  call Potato;"     // 6
      "  assign = line7;"  // 7
      "  }"
      "  assign = line8;"  // 8
      "}"
      "procedure Potato {"
      "  assign = line9;"  // 9
      "}";
  MockPKBWriter mockPKB(MOCK_WRITER_STORE);
  extractAbstraction(input, mockPKB, AbstractionType::CFG);

  IntToIntSetMap expectedNext = {{1, {2}}, {2, {3, 6}}, {3, {4, 5}}, {4, {3}},
                                 {5, {8}}, {6, {7}},    {7, {8}}};
  REQUIRE(mockPKB.isNextEqual(expectedNext));
}
