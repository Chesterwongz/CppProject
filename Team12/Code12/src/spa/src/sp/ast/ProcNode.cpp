#include "ProcNode.h"

void ProcNode::accept(Extractor *e) const {
    e->visitProcedure(this);
}

void ProcNode::reject(Extractor *e) const {
    e->postVisitProcedure(this);
}