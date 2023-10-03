#pragma once

#include "ArithmNode.h"
#include "sp/constants/OperatorConstants.h"

class MinusNode : public ArithmNode {
 public:
  MinusNode(std::unique_ptr<TNode> left, std::unique_ptr<TNode> right)
      : ArithmNode(TNodeType::TNODE_MINUS, op::kMinus, std::move(left),
                   std::move(right)) {}
};
