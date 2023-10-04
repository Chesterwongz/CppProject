#pragma once

#include <memory>
#include <string>

#include "CondNode.h"
#include "sp/constants/OperatorConstants.h"

class AndNode : public CondNode {
 public:
  AndNode(std::unique_ptr<TNode> left, std::unique_ptr<TNode> right)
      : CondNode(TNodeType::TNODE_AND, op::kAnd, std::move(left),
                 std::move(right)) {}
};
