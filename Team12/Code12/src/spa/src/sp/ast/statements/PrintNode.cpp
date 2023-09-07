#include "PrintNode.h"

void PrintNode::accept(Extractor *e) const {
    e->visitPrint(this);
}
