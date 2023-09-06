#pragma once

#include "ArithmNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class ModNode : public ArithmNode {
public:
    ModNode(std::unique_ptr<ExprNode> left, std::unique_ptr<ExprNode> right):
        ArithmNode(TNodeType::TNODE_MOD, kMod, std::move(left), std::move(right)) {}

};
