#pragma once

#include "RelNode.h"
#include "sp/constants/OperatorConstants.h"

class GtNode : public RelNode {
public:
    GtNode(std::unique_ptr<TNode> left, std::unique_ptr<TNode> right):
        RelNode(TNodeType::TNODE_GT, op::kGt, std::move(left), std::move(right)) {}

};

