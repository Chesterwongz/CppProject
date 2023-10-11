#pragma once

#include <string>
#include <utility>

#include "common/ast/TNode.h"

class ConstNode : public TNode {
 public:
  explicit ConstNode(string value)
      : TNode(TNodeType::TNODE_CONST, std::move(value)) {}
  void accept(Extractor& e) const override;
};
