#include "CondExprParser.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

std::optional<std::unique_ptr<TNode>> CondExprParser::parse() {
    if (!context->tryEatExpected(TokenType::DELIM, delim::kOpenBracketString).has_value())
        return std::nullopt;

    std::optional<std::unique_ptr<TNode>> nodeOpt;

    CondExprParser condExprParser = CondExprParser(context);
    std::optional<std::string> operatorOpt = context->tryEatExpected(TokenType::COND_OP, op::kNot);

    std::optional<std::unique_ptr<TNode>> leftNodeOpt = condExprParser.parse();
    if (leftNodeOpt.has_value()) {
        if (operatorOpt.has_value()) { // Since there was a '!' op, it's a unary expr.
            nodeOpt = std::make_unique<NotNode>(std::move(leftNodeOpt.value()));
        } else { // It's a binary expr.
            std::string condOp = context->forceEatExpected(TokenType::COND_OP);

            std::unique_ptr<TNode> rightNode = requireTNode(TNodeType::TNODE_COND)(condExprParser.parse());

            nodeOpt = ExprNodeFactory::makeNode(
                    condOp, std::move(leftNodeOpt.value()), std::move(rightNode));
        }
    }
    if (!nodeOpt.has_value()) { // was not a nested cond expr
        nodeOpt = RelExprParser(context).parse();
    }
    context->forceEatExpected(TokenType::DELIM, delim::kCloseBracketString);

    return nodeOpt;
}

#pragma clang diagnostic pop
