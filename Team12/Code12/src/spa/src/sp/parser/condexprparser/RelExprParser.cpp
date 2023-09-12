#include "RelExprParser.h"

//    rel_expr: rel_factor '>' rel_factor | rel_factor '>=' rel_factor |
//          rel_factor '<' rel_factor | rel_factor '<=' rel_factor |
//          rel_factor '==' rel_factor | rel_factor '!=' rel_factor
std::optional<std::unique_ptr<TNode>> RelExprParser::parse() {
    RelFactorParser relFactorParser = RelFactorParser(context);
    std::optional<std::unique_ptr<TNode>> leftNodeOpt = relFactorParser.parse();
    if (!leftNodeOpt.has_value()) return std::nullopt;

    std::optional<std::string> opOpt = context->tryEatExpected(TokenType::REL_OP);
    if (!opOpt.has_value()) return std::nullopt;

    std::unique_ptr<TNode> rightNode = requireTNode(TNodeType::TNODE_REL)(relFactorParser.parse());

    return ExprNodeFactory::makeNode(
            opOpt.value(), std::move(leftNodeOpt.value()), std::move(rightNode));
}
