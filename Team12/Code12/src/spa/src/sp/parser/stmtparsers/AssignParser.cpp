#include "AssignParser.h"

/* assign: var_name '=' expr ';'
 * var_name = parseName()
 * if var_name is NULL: return NULL
 * if parseKeyword('=') is NULL: throw SyntaxError
 * exprNode = parseExpr()
 * if tryEatExpected(';') is NULL: throw SyntaxError
 * node = AssignNode(var_name)
 * node.addChild(exprNode)
 * return node
 */
std::optional<std::unique_ptr<TNode>> AssignParser::parse() {
    if (!context->tryEatExpected(SpTokenType::DELIM, delim::kAssignString).has_value())
        return std::nullopt; // Not an assign stmt

    std::unique_ptr <TNode> varNode = std::make_unique<VarNode>(varName);

    std::optional <std::unique_ptr<TNode>> exprNodeOpt = ExprParser(context).parse();
    requireTNodeOpt(TNodeType::TNODE_ASSIGN)(exprNodeOpt);

    context->forceEatExpected(SpTokenType::DELIM, delim::kSemicolonString);

    std::unique_ptr <TNode> assignNode = std::make_unique<AssignNode>(context->getLineNum());
    assignNode->addChild(std::move(varNode));
    assignNode->addChild(std::move(exprNodeOpt.value()));
    return assignNode;
}
