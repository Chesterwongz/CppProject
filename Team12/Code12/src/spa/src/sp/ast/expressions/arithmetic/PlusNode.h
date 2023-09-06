#pragma once

#include "ArithmNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class PlusNode : public ArithmNode {
public:
    PlusNode(std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        ArithmNode(TNodeType::TNODE_PLUS, kPlus, std::move(left), std::move(right)) {}
};
