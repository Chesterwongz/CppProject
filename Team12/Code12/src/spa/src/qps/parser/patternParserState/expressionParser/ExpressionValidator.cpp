#include "ExpressionValidator.h"

bool ExpressionValidator::isValidExpression(const std::string& str) {
  try {
    std::optional<std::unique_ptr<TNode>> astOpt =
        ExprParser(std::move(std::make_shared<ParserContext>(str))).parse();
    return astOpt.has_value();
  } catch (SyntaxError& e) {
    return false;
  }
}
