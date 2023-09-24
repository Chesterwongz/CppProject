#pragma once

#include "RelNode.h"
#include "sp/constants/OperatorConstants.h"

class EqNode : public RelNode {
public:
    EqNode(std::unique_ptr<TNode> left, std::unique_ptr<TNode> right):
        RelNode(TNodeType::TNODE_EQ, op::kEq, std::move(left), std::move(right)) {}
};

