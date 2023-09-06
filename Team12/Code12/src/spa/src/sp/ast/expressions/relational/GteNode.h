#pragma once

#include "RelNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class GteNode : public RelNode {
public:
    GteNode(std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        RelNode(TNodeType::TNODE_GTE, kGte, std::move(left), std::move(right)) {}

};

