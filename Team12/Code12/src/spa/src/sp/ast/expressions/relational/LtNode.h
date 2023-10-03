#pragma once

#include "RelNode.h"
#include "sp/constants/OperatorConstants.h"

class LtNode : public RelNode {
 public:
  LtNode(std::unique_ptr<TNode> left, std::unique_ptr<TNode> right)
      : RelNode(TNodeType::TNODE_LT, op::kLt, std::move(left),
                std::move(right)) {}
};
