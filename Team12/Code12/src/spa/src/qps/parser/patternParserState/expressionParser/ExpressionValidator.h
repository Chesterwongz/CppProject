#pragma once

#include <memory>
#include <string>
#include <utility>

#include "common/ast/TNode.h"
#include "common/parser/exprparser/ExprParser.h"
#include "common/parser/parsercontext/ParserContext.h"

class ExpressionValidator {
 public:
  static bool isValidExpression(const std::string& str);
};
