#include "ConstParser.h"

std::optional<std::unique_ptr<TNode>> ConstParser::parse() {
  std::optional<std::string> constOpt =
      context.tryEatExpected(SpTokenType::INT);
  if (!constOpt.has_value()) return std::nullopt;
  return std::make_unique<ConstNode>(constOpt.value());
}
