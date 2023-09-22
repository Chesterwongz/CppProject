#include "IfNode.h"

void IfNode::accept(Extractor& e) const {
    e.visitIf(*this);
}

void IfNode::cleanup(Extractor& e) const {
    e.postVisitIf(*this);
}
