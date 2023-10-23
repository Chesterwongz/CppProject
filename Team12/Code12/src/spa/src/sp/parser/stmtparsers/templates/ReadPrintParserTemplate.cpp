#include "ReadPrintParserTemplate.h"

std::optional<std::unique_ptr<TNode>> ReadPrintParserTemplate::parse() {
  std::optional<std::unique_ptr<TNode>> varNodeOpt = VarParser(context).parse();
  if (!varNodeOpt.has_value()) return std::nullopt;  // not a read stmt

  context->forceEatExpected(SpTokenType::DELIM, delim::kSemicolonString);

  std::unique_ptr<TNode> node = makeTNode();
  node->addChild(std::move(varNodeOpt.value()));
  return node;
}
