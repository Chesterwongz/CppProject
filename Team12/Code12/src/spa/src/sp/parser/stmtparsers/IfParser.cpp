#include "IfParser.h"

// if: 'if' '(' cond_expr ')' 'then' '{' stmtLst '}' 'else' '{' stmtLst '}'
std::optional<std::unique_ptr<TNode>> IfParser::parse() {
    std::optional<std::unique_ptr<TNode>> condExprNodeOpt = CondExprParser(context).parse();
    if (!condExprNodeOpt.has_value()) return std::nullopt; // could be something like `if = 1;`

    std::unique_ptr<TNode> ifNode = std::make_unique<IfNode>(context->getLineNum());

    context->forceEatExpected(TokenType::NAME, keyword::kThen);

    std::unique_ptr<TNode> thenStmtLstNode = requireTNode(TNodeType::TNODE_IF)(StmtLstParser(context).parse());

    context->forceEatExpected(TokenType::NAME, keyword::kElse);

    std::unique_ptr<TNode> elseStmtLstNode = requireTNode(TNodeType::TNODE_IF)(StmtLstParser(context).parse());

    ifNode->addChild(std::move(condExprNodeOpt.value()));
    ifNode->addChild(std::move(thenStmtLstNode));
    ifNode->addChild(std::move(elseStmtLstNode));
    return ifNode;
}
