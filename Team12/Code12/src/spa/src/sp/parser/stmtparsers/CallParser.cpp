#include "CallParser.h"

std::optional<std::unique_ptr<TNode>> CallParser::parse() {
  std::optional<std::string> procNameOpt =
      context.tryEatExpected(SpTokenType::NAME);
  if (!procNameOpt.has_value()) return std::nullopt;  // not a call stmt

  context.forceEatExpected(SpTokenType::DELIM, delim::kSemicolonString);

  unique_ptr<TNode> callNode =
      std::make_unique<CallNode>(procNameOpt.value(), context.getLineNum());
  return callNode;
}
