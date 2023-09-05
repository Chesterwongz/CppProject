#pragma once

#include "RelNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class NeqNode : public RelNode {
public:
    NeqNode(std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        RelNode(TNodeType::TNODE_NEQ, kNeq, std::move(left), std::move(right)) {}

};

