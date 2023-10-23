#pragma once

#include <memory>
#include <string>
#include <utility>

#include "common/ast/TNode.h"

class ExprNode : public TNode {
 public:
  ExprNode(TNodeType nodeType, std::string value, std::unique_ptr<TNode> left,
           std::unique_ptr<TNode> right);
};
