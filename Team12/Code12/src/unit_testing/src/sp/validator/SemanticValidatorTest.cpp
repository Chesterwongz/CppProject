#include <catch.hpp>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common/parser/parsercontext/ParserContext.h"
#include "sp/ast/ProgramNode.h"
#include "sp/parser/toplevelparsers/ProgramParser.h"
#include "sp/validator/SemanticValidator.h"

using std::unique_ptr, std::make_unique, std::vector, std::string,
    std::unordered_map, std::unordered_set;

void setup(const string& input) {
  ParserContext context = ParserContext(input);
  std::optional<std::unique_ptr<TNode>> nodeOpt =
      ProgramParser(context).parse();
  if (!nodeOpt.has_value()) {
    throw SpException("Failed to parse input");
  }
  SemanticValidator semanticValidator;
  semanticValidator.validate(*nodeOpt.value());
}

TEST_CASE("SemanticValidator - valid program with one procedure") {
  string input =
      "procedure First {"
      "    read z;"
      "}";

  REQUIRE_NOTHROW(setup(input));
}

TEST_CASE("SemanticValidator - valid program with multi procedures") {
  std::string fileContent =
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
  REQUIRE_NOTHROW(setup(fileContent));
}

TEST_CASE("SemanticValidator - duplicate proc names throw exception") {
  string input =
      "procedure First {"
      "    read x;"
      "    read z;"
      "}"
      "procedure First {"
      "    print z;"
      "    read x;"
      "}";

  REQUIRE_THROWS_MATCHES(setup(input), DuplicateProcNameException,
                         Catch::Message("Duplicate procedure name 'First', "
                                        "this name has already been used!"));
}

TEST_CASE("SemanticValidator - undefined proc calls throw exception") {
  string input =
      "procedure First {"
      "    call Second;"
      "    read z;"
      "}"
      "procedure Second {"
      "    call Third;"
      "    read x;"
      "}"
      "procedure Third {"
      "    call Fourth;"
      "}";

  REQUIRE_THROWS_MATCHES(setup(input), UndefinedProcCallException,
                         Catch::Message("Procedure name 'Fourth' called has "
                                        "not been defined in the program!"));
}

TEST_CASE("CallsExtractor with parser - cyclic calls throw exception") {
  string input =
      "procedure First {"
      "    read x;"
      "    call First;"
      "}";

  REQUIRE_THROWS_MATCHES(setup(input), CyclicProcCallException,
                         Catch::Message("Cyclic procedure calls detected!"));
}
