#include <memory>
#include <optional>
#include <catch.hpp>

#include "common/ast/TNode.h"
#include "sp/parser/condexprparser/CondExprParser.h"
#include "sp/parser/toplevelparsers/ProgramParser.h"

TEST_CASE("Test ProgramParser") {
  std::string input =
      "\n procedure proc1 {\n\twhile(z >= 0){while((z!=0) || (!(z<0))){z = z*1 "
      "+ 2*3;}}\n\tprint z;}\nprocedure proc2 {\n\tprint = 1;read y;\n\n}\n";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      ProgramParser(parserContext).parse();
  REQUIRE(ast.has_value());
}

TEST_CASE("Test invalid program") {
  std::string input = "procedure proc {read a;}}";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      ProgramParser(parserContext).parse();
  REQUIRE(!parserContext.isEnd());
}

TEST_CASE("Test ProgramParser multi procedures") {
  std::string input =
      "procedure main {\n"
      "    flag = 0;\n"
      "    call computeCentroid;\n"
      "    call printResults;\n"
      "}\n"
      "procedure readPoint {\n"
      "    read x;\n"
      "    read y;\n"
      "}\n"
      "procedure printResults {\n"
      "    print flag;\n"
      "    print cenX;\n"
      "    print cenY;\n"
      "    print normSq;\n"
      "}\n"
      "procedure computeCentroid {\n"
      "    count = 0;\n"
      "    cenX = 0;\n"
      "    cenY = 0;\n"
      "    call readPoint;\n"
      "    while ((x != 0) && ((y - 1) > 0)) {\n"
      "        count = count + 1;\n"
      "        cenX = cenX + x;\n"
      "        cenY = cenY + y;\n"
      "        call readPoint;\n"
      "    }\n"
      "    if (count == 0) then {\n"
      "        flag = 1;\n"
      "    } else {\n"
      "        cenX = cenX / count;\n"
      "        cenY = cenY / count;\n"
      "    }\n"
      "    normSq = cenX * cenX + cenY * cenY;\n"
      "}";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      ProgramParser(parserContext).parse();
  REQUIRE(ast.has_value());
}

TEST_CASE("Nested Ifs") {
  std::string input =
      "procedure nestedIfs {\n"
      "    if (!(level == 1)) then {\n"
      "        assign = 2;\n"
      "        if ((level != 3) || (assign > 2))then{\n"
      "            assign = 4;\n"
      "        } else {\n"
      "            cenX = cenX / 5;\n"
      "            cenY = cenY / 6;\n"
      "        }\n"
      "    } else {\n"
      "        cenX = cenX / 7;\n"
      "        cenY = cenY / 8;\n"
      "    }\n"
      "}";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      ProgramParser(parserContext).parse();
  REQUIRE(ast.has_value());
}

TEST_CASE("Test BODMAS") {
  std::string input = "hi = (1* (1 + 2) + (0) /2)%2;";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      StmtParser(parserContext).parse();
  REQUIRE(ast.has_value());
}

TEST_CASE("Test assign multibrackets") {
  std::string input = "hi = ((line6 )- 1);";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      StmtParser(parserContext).parse();
  REQUIRE(ast.has_value());
}

TEST_CASE("Test invalid assign stmt") {
  std::string input = "hi = ();";
  try {
    ParserContext parserContext = ParserContext(input);
    std::optional<std::unique_ptr<TNode>> ast =
        StmtParser(parserContext).parse();
    REQUIRE(false);
  } catch (const SpSyntaxError& err) {
    std::string errMsg(err.what());
    REQUIRE(!errMsg.empty());
  }
}

TEST_CASE("Test RelFactor multibrackets") {
  std::string input = "((line6 )- 1) > (a - 1)";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      RelExprParser(parserContext).parse();
  REQUIRE(ast.has_value());
}

TEST_CASE("Test WhileParser") {
  std::string input =
      "while ((((line6 )- 1) > (a - 1)) && (!(1 != 1))) {\n"
      "        line7 = a + 1;\n"
      "    }";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      StmtParser(parserContext).parse();
  REQUIRE(ast.has_value());
  REQUIRE(ast.value()
              ->getChildAt(0)
              .getChildAt(0)
              .getChildAt(0)
              .getChildAt(0)
              .isEqual(VarNode("line6")));
}

TEST_CASE("Test CondExprParser Not cond brackets") {
  std::string input = "!(1 != 1)";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      CondExprParser(parserContext).parse();
  REQUIRE(ast.has_value());
}

TEST_CASE("Test CondExprParser multiple brackets") {
  std::string input = "(((line6 )- 1) > (a - 1)) && (!(1 != 1))";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      CondExprParser(parserContext).parse();
  REQUIRE(ast.has_value());
  REQUIRE(ast.value()->getChildAt(0).getChildAt(0).getChildAt(0).isEqual(
      VarNode("line6")));
}

TEST_CASE("Test CondExprParser complex exprs") {
  std::string input =
      "(line7 * 7 == (line7 + 7)%7)||(! ( line7/line7 != line7/line7+7)))";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      CondExprParser(parserContext).parse();
  REQUIRE(ast.has_value());
  //    REQUIRE(ast.value()->getChildAt(0).getChildAt(0).getChildAt(0).isEqual(VarNode("line6")));
}

TEST_CASE("Test CondExprParser") {
  std::string input = "(((z) - 1)!=(0)) || (!(z<0))";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      CondExprParser(parserContext).parse();
  REQUIRE(ast.has_value());
}

TEST_CASE("Test CondExprParser is RelExpr") {
  std::string input = "(p) == 2";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      CondExprParser(parserContext).parse();
  REQUIRE(ast.has_value());
}

TEST_CASE("Test CondExprParser is (RelExpr)") {
  std::string input = "((p + q * 2) == (x - y % 3))";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      CondExprParser(parserContext).parseWithBrackets();
  REQUIRE(ast.has_value());
}

TEST_CASE("Test RelExprParser expr == (expr)%factor") {
  std::string input = "line7 * 7 == (line7 + 7)%7";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      RelExprParser(parserContext).parse();
  REQUIRE(ast.has_value());
}

TEST_CASE("Test RelExprParser (expr) == (expr)") {
  std::string input = "p + q== x - y";
  ParserContext parserContext = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> ast =
      RelExprParser(parserContext).parse();
  REQUIRE(ast.has_value());
}
