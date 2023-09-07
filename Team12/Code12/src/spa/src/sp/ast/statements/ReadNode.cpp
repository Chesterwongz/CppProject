#include "ReadNode.h"

void ReadNode::accept(Extractor *e) const {
    e->visitRead(this);
}
