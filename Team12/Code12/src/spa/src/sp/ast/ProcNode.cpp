#include "ProcNode.h"

void ProcNode::accept(Extractor *e) const {
    e->visitProcedure(this);
}