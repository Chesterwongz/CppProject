#pragma once

#include <memory>
#include <utility>

#include "ArithmNode.h"
#include "sp/constants/OperatorConstants.h"

class PlusNode : public ArithmNode {
 public:
  PlusNode(std::unique_ptr<TNode> left, std::unique_ptr<TNode> right)
      : ArithmNode(TNodeType::TNODE_PLUS, op::kPlus, std::move(left),
                   std::move(right)) {}
};
