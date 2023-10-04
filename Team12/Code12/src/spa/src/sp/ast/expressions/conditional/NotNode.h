#pragma once

#include <memory>
#include <string>

#include "CondNode.h"
#include "sp/constants/OperatorConstants.h"

class NotNode : public CondNode {
 public:
  explicit NotNode(std::unique_ptr<TNode> left)
      : CondNode(TNodeType::TNODE_NOT, op::kNot, std::move(left), nullptr) {}
};
