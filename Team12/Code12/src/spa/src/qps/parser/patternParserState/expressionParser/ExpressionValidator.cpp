#include "ExpressionValidator.h"

bool ExpressionValidator::isValidExpression(const std::string& str) {
  bool res = false;
  try {
    std::optional<std::unique_ptr<TNode>> astOpt =
        ExprParser(std::move(std::make_shared<ParserContext>(str))).parse();
    res = astOpt.has_value();
  } catch (SyntaxError& e) {
    return false;
  }
  return res;
}
