#pragma once

#include "sp/ast/expressions/ExprNode.h"

class RelNode : public ExprNode {
public:
    RelNode(TNodeType nodeType, std::string value, std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        ExprNode(nodeType, std::move(value), std::move(left), std::move(right)) {}
};
