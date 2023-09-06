#pragma once

#include "ArithmNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class DivNode : public ArithmNode {
public:
    DivNode(std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        ArithmNode(TNodeType::TNODE_DIV, kDiv, std::move(left), std::move(right)) {}
};


