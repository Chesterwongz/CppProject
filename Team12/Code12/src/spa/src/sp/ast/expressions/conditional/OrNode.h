#pragma once

#include "CondNode.h"
#include "sp/constants/OperatorConstants.h"

class OrNode : public CondNode {
public:
    OrNode(std::unique_ptr<TNode> left, std::unique_ptr<TNode> right):
        CondNode(TNodeType::TNODE_OR, op::kOr, std::move(left), std::move(right)) {}

};

