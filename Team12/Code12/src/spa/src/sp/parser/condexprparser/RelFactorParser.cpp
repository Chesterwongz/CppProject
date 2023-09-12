#include "RelFactorParser.h"

//    rel_factor: var_name | const_value | expr
std::optional<std::unique_ptr<TNode>> RelFactorParser::parse() {
    std::optional<std::unique_ptr<TNode>> nodeOpt = VarParser(context).parse();
    if (nodeOpt.has_value()) return nodeOpt;

    nodeOpt = ConstParser(context).parse();
    if (nodeOpt.has_value()) return nodeOpt;

    nodeOpt = ExprParser(context).parse();
    return nodeOpt;
}
