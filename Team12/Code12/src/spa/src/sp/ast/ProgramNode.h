#pragma once

#include "TNode.h"

class ProgramNode : public TNode {
public:
    ProgramNode(): TNode(TNodeType::TNODE_PROGRAM) {}
    void accept(Extractor* e) const override;
};

