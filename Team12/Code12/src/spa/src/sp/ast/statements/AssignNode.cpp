#include "AssignNode.h"

void AssignNode::accept(Extractor& e) const { e.visitAssign(*this); }

void AssignNode::cleanup(Extractor& e) const { e.postVisitAssign(*this); }
