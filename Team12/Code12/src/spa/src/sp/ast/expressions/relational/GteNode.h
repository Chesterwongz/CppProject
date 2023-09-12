#pragma once

#include "RelNode.h"
#include "sp/constants/OperatorConstants.h"

class GteNode : public RelNode {
public:
    GteNode(std::unique_ptr<TNode> left, std::unique_ptr<TNode> right):
        RelNode(TNodeType::TNODE_GTE, op::kGte, std::move(left), std::move(right)) {}

};

