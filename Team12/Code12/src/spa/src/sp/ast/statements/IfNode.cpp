#include "IfNode.h"

void IfNode::accept(Extractor *e) const {
    e->visitIf(this);
}
