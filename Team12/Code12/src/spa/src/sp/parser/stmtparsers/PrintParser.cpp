#include "PrintParser.h"

//print: 'print' var_name';'
std::optional<std::unique_ptr<TNode>> PrintParser::parse() {
    std::optional<std::unique_ptr<TNode>> varNodeOpt = VarParser(context).parse();
    if (!varNodeOpt.has_value()) return std::nullopt; // not a print stmt

    context->forceEatExpected(TokenType::DELIM, delim::kSemicolonString);

    std::unique_ptr<TNode> printNode = std::make_unique<PrintNode>(context->getLineNum());
    printNode->addChild(std::move(varNodeOpt.value()));
    return printNode;
}
