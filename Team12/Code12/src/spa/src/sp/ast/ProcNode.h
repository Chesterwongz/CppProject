#pragma once

#include <string>
#include <utility>

#include "StmtListNode.h"
#include "common/ast/TNode.h"

class ProcNode : public TNode {
 public:
  explicit ProcNode(std::string name)
      : TNode(TNodeType::TNODE_PROCEDURE, std::move(name)) {}
  void accept(Extractor& e) const override;
  void cleanup(Extractor& e) const override;
};
