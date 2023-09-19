#pragma once

#include <string>
#include "TNode.h"
#include "sp/ast/ProgramNode.h"

class ProgramNode : public TNode {
public:
    ProgramNode(): TNode(TNodeType::TNODE_PROGRAM) {}
    void accept(Extractor* e) const override;
    void cleanup(Extractor* e) const override;
};
