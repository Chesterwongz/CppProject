#include "StmtListNode.h"

void StmtListNode::accept(Extractor *e) const {
    e->visitStmtList(this);
}

void StmtListNode::cleanup(Extractor *e) const {
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

int StmtListNode::getStartLineNum() const {
    auto* firstStmtChild = dynamic_cast<StmtNode*>(this->getChildren()[0]);
    return firstStmtChild->getLineNum();
}
