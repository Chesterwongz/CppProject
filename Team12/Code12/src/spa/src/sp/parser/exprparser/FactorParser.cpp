#include "FactorParser.h"

//    factor: var_name | const_value | '(' expr ')'
std::optional<std::unique_ptr<TNode>> FactorParser::parse() {
    std::optional<std::unique_ptr<TNode>> nodeOpt = VarParser(context).parse();
    if (nodeOpt.has_value()) return nodeOpt;

    nodeOpt = ConstParser(context).parse();
    if (nodeOpt.has_value()) return nodeOpt;

    context->forceEatExpected(TokenType::DELIM, delim::kOpenBracketString);
    nodeOpt = ExprParser(context).parse();
    requireTNodeOpt(TNodeType::TNODE_FACTOR)(nodeOpt);
    context->forceEatExpected(TokenType::DELIM, delim::kCloseBracketString);

    return nodeOpt;
}
