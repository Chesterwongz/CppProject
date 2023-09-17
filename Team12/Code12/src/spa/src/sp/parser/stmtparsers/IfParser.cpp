#include "IfParser.h"

// if: 'if' '(' cond_expr ')' 'then' '{' stmtLst '}' 'else' '{' stmtLst '}'
std::optional<std::unique_ptr<TNode>> IfParser::parse() {
    std::optional<std::unique_ptr<TNode>> condExprNodeOpt = CondExprParser(context).parse();
    if (!condExprNodeOpt.has_value()) return std::nullopt; // could be something like `if = 1;`

    context->forceEatExpected(TokenType::NAME, keyword::kThen);

    StmtLstParser parser = StmtLstParser(context);

    std::optional<std::unique_ptr<TNode>> thenStmtLstNodeOpt = parser.parse();
    requireTNodeOpt(TNodeType::TNODE_IF)(thenStmtLstNodeOpt);

    context->forceEatExpected(TokenType::NAME, keyword::kElse);

    std::optional<std::unique_ptr<TNode>> elseStmtLstNodeOpt = parser.parse();
    requireTNodeOpt(TNodeType::TNODE_IF)(elseStmtLstNodeOpt);

    std::unique_ptr<TNode> ifNode = std::make_unique<IfNode>(context->getLineNum());
    ifNode->addChild(std::move(condExprNodeOpt.value()));
    ifNode->addChild(std::move(thenStmtLstNodeOpt.value()));
    ifNode->addChild(std::move(elseStmtLstNodeOpt.value()));

    return ifNode;
}
