#include "CallNode.h"

void CallNode::accept(Extractor& e) const { e.visitCall(*this); }
