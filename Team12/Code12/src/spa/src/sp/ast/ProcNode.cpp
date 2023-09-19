#include "ProcNode.h"

void ProcNode::accept(Extractor *e) const {
    e->visitProcedure(*this);
}

void ProcNode::cleanup(Extractor *e) const {
    e->postVisitProcedure(*this);
}

int ProcNode::getProcStart() const {
    auto* stmtListNode = dynamic_cast<StmtListNode*>(this->getChildren()[0]);
    return stmtListNode->getStartLineNum();
}