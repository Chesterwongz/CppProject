#pragma once

#include "RelNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class GtNode : public RelNode {
public:
    GtNode(std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        RelNode(TNodeType::TNODE_GT, kGt, std::move(left), std::move(right)) {}

};

