#include "StmtListNode.h"

void StmtListNode::accept(Extractor *e) const {
    e->visitStmtList(this);
}

void StmtListNode::reject(Extractor *e) const {
    e->postVisitStmtList(this);
}

// ai-gen start (gpt-4, 1)
std::vector<int> StmtListNode::getChildrenLineNums() const {
    std::vector<int> childrenLineNums;
    for (TNode* child : TNode::getChildren()) {
        auto* stmtChild = dynamic_cast<StmtNode*>(child);
        if (stmtChild) {
            childrenLineNums.push_back(stmtChild->getLineNum());
        }
    }
    return childrenLineNums;
}
// ai-gen end
