#include "WhileNode.h"

void WhileNode::accept(Extractor& e) const {
    e.visitWhile(*this);
}

void WhileNode::cleanup(Extractor& e) const {
    e.postVisitWhile(*this);
}