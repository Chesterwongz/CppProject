#include "ProgramNode.h"

void ProgramNode::accept(Extractor *e) const {
    e->visitProgram(this);
}
