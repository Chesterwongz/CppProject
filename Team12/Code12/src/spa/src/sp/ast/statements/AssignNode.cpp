#include "AssignNode.h"

void AssignNode::accept(Extractor *e) const {
    e->visitAssign(this);
}
