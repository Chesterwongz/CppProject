#include "ProcNode.h"

void ProcNode::accept(Extractor *e) const {
    e->visitProcedure(this);
}

void ProcNode::cleanup(Extractor *e) const {
    e->postVisitProcedure(this);
}