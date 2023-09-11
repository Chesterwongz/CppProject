#pragma once

#include "TNode.h"

class ProgramNode : public TNode {
public:
    explicit ProgramNode() : TNode(TNodeType::TNODE_PROGRAM) {}
};

