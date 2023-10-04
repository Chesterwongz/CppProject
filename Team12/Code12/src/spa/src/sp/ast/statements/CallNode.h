#pragma once

#include <string>
#include <utility>

#include "StmtNode.h"

class CallNode : public StmtNode {
 public:
  CallNode(std::string procName, int lineNum)
      : StmtNode(TNodeType::TNODE_CALL, std::move(procName), lineNum) {}
  void accept(Extractor& e) const override;
};
