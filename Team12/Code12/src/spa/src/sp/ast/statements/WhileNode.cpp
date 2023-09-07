#include "WhileNode.h"

void WhileNode::accept(Extractor *e) const {
    e->visitWhile(this);
}

void WhileNode::reject(Extractor *e) const {
    e->postVisitWhile(this);
}