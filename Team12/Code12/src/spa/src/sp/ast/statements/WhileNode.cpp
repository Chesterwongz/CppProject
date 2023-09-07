#include "WhileNode.h"

void WhileNode::accept(Extractor *e) const {
    e->visitWhile(this);
}
