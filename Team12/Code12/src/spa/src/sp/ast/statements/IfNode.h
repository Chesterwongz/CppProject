#pragma once

#include "StmtNode.h"

class IfNode : public StmtNode {
 public:
  explicit IfNode(int lineNum) : StmtNode(TNodeType::TNODE_IF, "", lineNum) {}
  void accept(Extractor& e) const override;
  void cleanup(Extractor& e) const override;
};
