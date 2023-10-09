#include "AbstractParser.h"

std::function<void(const std::optional<std::unique_ptr<TNode>> &)>
AbstractParser::requireTNodeOpt(TNodeType nodeType) {
  int lineNum = context->getLineNum();
  return [nodeType,
          lineNum](const std::optional<std::unique_ptr<TNode>> &nodeOpt) {
    if (!nodeOpt.has_value())
      throw SpSyntaxError(TNodeTypeUtils::toString(nodeType), lineNum);
  };
}

std::optional<std::unique_ptr<TNode>> AbstractParser::parseWithBrackets() {
  context->saveContext();
  if (!context->tryEatExpected(SpTokenType::DELIM, delim::kOpenBracketString)
           .has_value()) {
    context->loadPrevSavedContext();
    return std::nullopt;
  }

  std::optional<std::unique_ptr<TNode>> nodeOpt = parse();

  if (!nodeOpt.has_value() ||
      !context->tryEatExpected(SpTokenType::DELIM, delim::kCloseBracketString)
           .has_value()) {
    context->loadPrevSavedContext();
    return std::nullopt;
  }
  context->removePrevSavedContext();
  return nodeOpt;
}
