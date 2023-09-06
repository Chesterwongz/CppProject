#pragma once

#include "TNode.h"

class ProcNode : public TNode {
public:
    explicit ProcNode(std::string name): TNode(TNodeType::TNODE_PROCEDURE, std::move(name)) {}
};
