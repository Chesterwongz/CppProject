#include "WhileParser.h"

// while: 'while' '(' cond_expr ')' '{' stmtLst '}'
std::optional<std::unique_ptr<TNode>> WhileParser::parse() {
    std::optional<std::unique_ptr<TNode>> condExprNodeOpt = CondExprParser(context).parseWithBrackets();
    if (!condExprNodeOpt.has_value()) return std::nullopt; // could be something like `while = 1;`

    std::unique_ptr<TNode> whileNode = std::make_unique<WhileNode>(context->getLineNum());

    std::optional<std::unique_ptr<TNode>> stmtLstNodeOpt = StmtLstParser(context).parse();
    requireTNodeOpt(TNodeType::TNODE_WHILE)(stmtLstNodeOpt);

    whileNode->addChild(std::move(condExprNodeOpt.value()));
    whileNode->addChild(std::move(stmtLstNodeOpt.value()));
    return whileNode;
}
