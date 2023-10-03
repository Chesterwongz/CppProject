#pragma once

#include "sp/ast/expressions/ExprNode.h"

class CondNode : public ExprNode {
 public:
  CondNode(TNodeType nodeType, std::string value, std::unique_ptr<TNode> left,
           std::unique_ptr<TNode> right)
      : ExprNode(nodeType, std::move(value), std::move(left),
                 std::move(right)) {}
};
