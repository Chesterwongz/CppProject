#include "ReadParser.h"

std::optional<std::unique_ptr<TNode>> ReadParser::parse() {
    std::optional<std::unique_ptr<TNode>> varNodeOpt = VarParser(context).parse();
    if (!varNodeOpt.has_value()) return std::nullopt; // not a read stmt

    context->forceEatExpected(TokenType::DELIM, delim::kSemicolonString);

    std::unique_ptr<TNode> readNode = std::make_unique<ReadNode>(context->getLineNum());
    readNode->addChild(std::move(varNodeOpt.value()));
    return readNode;
}
