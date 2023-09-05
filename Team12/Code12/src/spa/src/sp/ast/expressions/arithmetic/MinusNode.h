#pragma once

#include "ArithmNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class MinusNode : public ArithmNode {
public:
    MinusNode(std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        ArithmNode(TNodeType::TNODE_MINUS, kMinus, std::move(left), std::move(right)) {}

};

