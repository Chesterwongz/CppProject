#include "CondExprParser.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

std::optional<std::unique_ptr<TNode>> CondExprParser::parse() {
    std::optional<std::unique_ptr<TNode>> nodeOpt;
    CondExprParser condExprParser = CondExprParser(context);
    std::optional<std::string> operatorOpt = context->tryEatExpected(TokenType::COND_OP, op::kNot);

    std::optional<std::unique_ptr<TNode>> leftNodeOpt = condExprParser.parseWithBrackets();
    if (leftNodeOpt.has_value()) {
        if (operatorOpt.has_value()) { // Since there was a '!' op, it's a unary expr.
            nodeOpt = std::make_unique<NotNode>(std::move(leftNodeOpt.value()));
        } else { // It's a binary expr.
            std::string condOp = context->forceEatExpected(TokenType::COND_OP);

            std::optional<std::unique_ptr<TNode>> rightNodeOpt = condExprParser.parseWithBrackets();
            requireTNodeOpt(TNodeType::TNODE_COND)(rightNodeOpt);

            nodeOpt = ExprNodeFactory::makeNode(
                    condOp, std::move(leftNodeOpt.value()), std::move(rightNodeOpt.value()));
        }
    }
    if (!nodeOpt.has_value()) { // was not a nested cond expr
        nodeOpt = RelExprParser(context).parse();
    }

    return nodeOpt;
}

#pragma clang diagnostic pop
