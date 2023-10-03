#include "VarNode.h"

void VarNode::accept(Extractor& e) const { e.visitVariable(*this); }