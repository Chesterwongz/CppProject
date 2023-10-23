#pragma once

#include <string>
#include <utility>

#include "common/ast/TNode.h"

class VarNode : public TNode {
 public:
  explicit VarNode(string value)
      : TNode(TNodeType::TNODE_VAR, std::move(value)) {}
  void accept(Extractor& e) const override;
};
