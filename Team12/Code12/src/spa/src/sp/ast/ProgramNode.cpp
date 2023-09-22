#include "ProgramNode.h"

void ProgramNode::accept(Extractor& e) const {
    e.visitProgram(*this);
}

void ProgramNode::cleanup(Extractor& e) const {
    e.postVisitProgram(*this);
}
