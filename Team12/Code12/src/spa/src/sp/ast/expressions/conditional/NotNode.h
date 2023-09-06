#pragma once

#include "CondNode.h"
#include "sp/utils/ExprSymbolUtils.h"

class NotNode : public CondNode {
public:
    explicit NotNode(std::unique_ptr<ExprNode> left):
        CondNode(TNodeType::TNODE_NOT, kNot, std::move(left), nullptr) {}

};

