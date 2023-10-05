#pragma once

#include <memory>
#include <string>
#include <utility>

#include "RelNode.h"
#include "sp/constants/OperatorConstants.h"

class LteNode : public RelNode {
 public:
  LteNode(std::unique_ptr<TNode> left, std::unique_ptr<TNode> right)
      : RelNode(TNodeType::TNODE_LTE, op::kLte, std::move(left),
                std::move(right)) {}
};
