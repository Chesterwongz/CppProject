#pragma once

#include "CondNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class AndNode : public CondNode {
public:
    AndNode(std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        CondNode(TNodeType::TNODE_AND, kAnd, std::move(left), std::move(right)) {}

};

