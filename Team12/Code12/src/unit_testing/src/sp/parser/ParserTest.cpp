#include <optional>
#include <memory>

#include "sp/ast/TNode.h"

#include "catch.hpp"
#include "sp/parser/toplevelparsers/ProgramParser.h"
#include "sp/parser/condexprparser/CondExprParser.h"

TEST_CASE("Test ProgramParser") {
    std::string input = "\n procedure proc1 {\n\twhile(z >= 0){while((z!=0) || (!(z<0))){z = z*1 + 2*3;}}\n\tprint z;}\nprocedure proc2 {\n\tprint = 1;read y;\n\n}\n";
    std::optional<std::unique_ptr<TNode>> ast = ProgramParser(std::move(std::make_shared<ParserContext>(std::move(input)))).parse();
    REQUIRE(ast.has_value());
}

TEST_CASE("Test ProgramParser multi procedures") {
    std::string fileContent = "procedure main {\n"
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
                              "    while ((x != 0) && (y != 0)) {\n"
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
    std::optional<std::unique_ptr<TNode>> ast =
            ProgramParser(std::move(std::make_shared<ParserContext>(std::move(fileContent)))).parse();
    REQUIRE(ast.has_value());
}

TEST_CASE("Test BODMAS") {
    std::string input = "hi = (1* (1 + 2) + (0) /2)%2;";
    std::optional<std::unique_ptr<TNode>> ast = StmtParser(std::move(std::make_shared<ParserContext>(std::move(input)))).parse();
    REQUIRE(ast.has_value());
}

TEST_CASE("Test CondExprParser") {
    std::string input = "((z!=0) || (!(z<0)))";
    std::optional<std::unique_ptr<TNode>> ast = CondExprParser(std::move(std::make_shared<ParserContext>(std::move(input)))).parse();
    REQUIRE(ast.has_value());
}
