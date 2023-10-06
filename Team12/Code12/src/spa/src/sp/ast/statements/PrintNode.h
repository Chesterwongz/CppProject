#pragma once

#include "StmtNode.h"

class PrintNode : public StmtNode {
 public:
  explicit PrintNode(int lineNum)
      : StmtNode(TNodeType::TNODE_PRINT, "", lineNum) {}
  void accept(Extractor& e) const override;
  void cleanup(Extractor& e) const override;
};
