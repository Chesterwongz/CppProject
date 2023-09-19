#include "PrintNode.h"

void PrintNode::accept(Extractor *e) const {
    e->visitPrint(*this);
}

void PrintNode::cleanup(Extractor *e) const {
    e->postVisitPrint(*this);
}
