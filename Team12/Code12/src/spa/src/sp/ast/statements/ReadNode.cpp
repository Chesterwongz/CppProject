#include "ReadNode.h"

void ReadNode::accept(Extractor *e) const {
    e->visitRead(*this);
}

void ReadNode::cleanup(Extractor *e) const {
    e->postVisitRead(*this);
}
