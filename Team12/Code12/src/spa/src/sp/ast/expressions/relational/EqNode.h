#pragma once

#include "RelNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class EqNode : public RelNode {
public:
    EqNode(std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        RelNode(TNodeType::TNODE_EQ, kEq, std::move(left), std::move(right)) {}

};

