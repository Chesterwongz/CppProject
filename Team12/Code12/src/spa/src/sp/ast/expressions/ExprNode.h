#pragma once

#include <utility>

#include "sp/ast/TNode.h"

class ExprNode : public TNode {
public:
    explicit ExprNode(TNodeType nodeType, std::string value): TNode(nodeType, std::move(value)) {}
    ExprNode(TNodeType nodeType, std::string value, std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right): TNode(nodeType, std::move(value)) {
        addChild(std::move(left));
        addChild(std::move(right));
    }
};


