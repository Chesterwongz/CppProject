#pragma once

#include <memory>
#include <utility>

#include "ArithmNode.h"
#include "sp/constants/OperatorConstants.h"

class ModNode : public ArithmNode {
 public:
  ModNode(std::unique_ptr<TNode> left, std::unique_ptr<TNode> right)
      : ArithmNode(TNodeType::TNODE_MOD, op::kMod, std::move(left),
                   std::move(right)) {}
};
