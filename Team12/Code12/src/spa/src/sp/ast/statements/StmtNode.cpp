#include "StmtNode.h"

int StmtNode::getLineNum() const { return lineNum; }

// ai-gen start (gpt-4, 0)
// prompt: StmtNode extends from TNode with additional private attribute lineNum
// and a public getLineNum, how do I do the additional lineNum check
bool StmtNode::isEqual(const TNode& other) const {
  // check if same type
  const auto* otherStmtNode = dynamic_cast<const StmtNode*>(&other);
  if (!otherStmtNode) {
    return false;
  }

  if (lineNum != otherStmtNode->getLineNum()) {
    return false;
  }

  return TNode::isEqual(other);
}
// ai-gen end
