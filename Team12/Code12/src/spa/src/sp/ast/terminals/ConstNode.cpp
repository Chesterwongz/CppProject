#include "ConstNode.h"

void ConstNode::accept(Extractor& e) const { e.visitConstant(*this); }
