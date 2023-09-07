#include "StmtListNode.h"

void StmtListNode::accept(Extractor *e) const {
    e->visitStmtList(this);
}
