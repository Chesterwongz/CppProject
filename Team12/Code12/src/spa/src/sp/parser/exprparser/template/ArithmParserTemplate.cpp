#include "ArithmParserTemplate.h"

//    expr: expr '+' term | expr '-' term | term
//    term: term '*' factor | term '/' factor | term '%' factor | factor
std::optional<std::unique_ptr<TNode>> ArithmParserTemplate::parse() {
    std::unique_ptr<AbstractParser> parser = getNextParser();
    std::optional<std::unique_ptr<TNode>> leftNodeOpt = parser->parse();
    if (!leftNodeOpt.has_value()) return std::nullopt;

    std::optional<std::string> opOpt = context->tryEatExpected(getExpectedTokenType());
    while (opOpt.has_value()) {
        std::unique_ptr<TNode> rightNode = requireTNode(getExpectedTNodeType())(parser->parse());

        leftNodeOpt = ExprNodeFactory::makeNode(
                opOpt.value(), std::move(leftNodeOpt.value()), std::move(rightNode));

        opOpt = context->tryEatExpected(getExpectedTokenType());
    }
    return leftNodeOpt;
}
