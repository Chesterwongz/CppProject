#pragma once

#include "CondNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class OrNode : public CondNode {
public:
    OrNode(std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        CondNode(TNodeType::TNODE_OR, kOr, std::move(left), std::move(right)) {}

};

