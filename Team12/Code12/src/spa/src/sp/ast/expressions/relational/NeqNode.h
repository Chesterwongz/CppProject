#pragma once

#include "RelNode.h"
#include "sp/constants/OperatorConstants.h"

class NeqNode : public RelNode {
public:
    NeqNode(std::unique_ptr<TNode> left, std::unique_ptr<TNode> right):
        RelNode(TNodeType::TNODE_NEQ, op::kNeq, std::move(left), std::move(right)) {}

};

