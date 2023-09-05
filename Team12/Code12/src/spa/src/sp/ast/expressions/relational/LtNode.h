#pragma once

#include "RelNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class LtNode : public RelNode {
public:
    LtNode(std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        RelNode(TNodeType::TNODE_LT, kLt, std::move(left), std::move(right)) {}

};

