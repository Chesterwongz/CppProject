#include "VarParser.h"

std::optional<std::unique_ptr<TNode>> VarParser::parse() {
  std::optional<std::string> varNameOpt =
      context->tryEatExpected(SpTokenType::NAME);
  if (!varNameOpt.has_value()) return std::nullopt;
  return std::make_unique<VarNode>(varNameOpt.value());
}
