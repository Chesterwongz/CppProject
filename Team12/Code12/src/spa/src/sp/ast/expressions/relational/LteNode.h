#pragma once

#include "RelNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class LteNode : public RelNode {
public:
    LteNode(std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        RelNode(TNodeType::TNODE_LTE, kLte, std::move(left), std::move(right)) {}

};

