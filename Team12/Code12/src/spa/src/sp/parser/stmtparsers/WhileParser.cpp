#include "WhileParser.h"

// while: 'while' '(' cond_expr ')' '{' stmtLst '}'
std::optional<std::unique_ptr<TNode>> WhileParser::parse() {
    std::optional<std::unique_ptr<TNode>> condExprNodeOpt = CondExprParser(context).parse();
    if (!condExprNodeOpt.has_value()) return std::nullopt; // could be something like `while = 1;`

    std::unique_ptr<TNode> whileNode = std::make_unique<WhileNode>(context->getLineNum());

    std::unique_ptr<TNode> stmtLstNode = requireTNode(TNodeType::TNODE_WHILE)(
            StmtLstParser(context).parse());

    whileNode->addChild(std::move(condExprNodeOpt.value()));
    whileNode->addChild(std::move(stmtLstNode));
    return whileNode;
}
