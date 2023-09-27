#include "RelExprParser.h"

//    rel_expr: rel_factor '>' rel_factor | rel_factor '>=' rel_factor |
//          rel_factor '<' rel_factor | rel_factor '<=' rel_factor |
//          rel_factor '==' rel_factor | rel_factor '!=' rel_factor
std::optional<std::unique_ptr<TNode>> RelExprParser::parse() {
    RelFactorParser relFactorParser = RelFactorParser(context);
    std::optional<std::unique_ptr<TNode>> leftNodeOpt = relFactorParser.parse();
    if (!leftNodeOpt.has_value()) return std::nullopt;

    std::optional<std::string> opOpt = context->tryEatExpected(SpTokenType::REL_OP);
    if (!opOpt.has_value()) return std::nullopt;

    std::optional<std::unique_ptr<TNode>> rightNodeOpt = relFactorParser.parse();
    requireTNodeOpt(TNodeType::TNODE_REL)(rightNodeOpt);

    return ExprNodeFactory::makeNode(
            opOpt.value(), std::move(leftNodeOpt.value()), std::move(rightNodeOpt.value()));
}
