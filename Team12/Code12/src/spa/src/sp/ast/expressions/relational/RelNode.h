#pragma once

#include <memory>
#include <string>
#include <utility>

#include "sp/ast/expressions/ExprNode.h"

class RelNode : public ExprNode {
 public:
  RelNode(TNodeType nodeType, std::string value, std::unique_ptr<TNode> left,
          std::unique_ptr<TNode> right)
      : ExprNode(nodeType, std::move(value), std::move(left),
                 std::move(right)) {}
};
