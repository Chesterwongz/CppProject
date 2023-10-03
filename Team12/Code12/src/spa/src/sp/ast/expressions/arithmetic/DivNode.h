#pragma once

#include "ArithmNode.h"
#include "sp/constants/OperatorConstants.h"

class DivNode : public ArithmNode {
 public:
  DivNode(std::unique_ptr<TNode> left, std::unique_ptr<TNode> right)
      : ArithmNode(TNodeType::TNODE_DIV, op::kDiv, std::move(left),
                   std::move(right)) {}
};
