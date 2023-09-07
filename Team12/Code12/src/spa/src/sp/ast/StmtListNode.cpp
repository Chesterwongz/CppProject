#include "StmtListNode.h"

void StmtListNode::accept(Extractor *e) const {
    e->visitStmtList(this);
}

void StmtListNode::reject(Extractor *e) const {
    e->postVisitStmtList(this);
}