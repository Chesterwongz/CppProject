#include "ExpressionValidator.h"

bool ExpressionValidator::isValidExpression(const std::string& str) {
  try {
    std::shared_ptr<ParserContext> parserContext =
        std::make_shared<ParserContext>(str);
    std::optional<std::unique_ptr<TNode>> astOpt =
        ExprParser(parserContext).parse();
    return parserContext->isEnd() && astOpt.has_value();
  } catch (CommonSyntaxError& e) {
    return false;
  } catch (SpSyntaxError& e) {
    return false;
  }
}
