#pragma once

#include <utility>

#include "TNode.h"

class ProcNode : public TNode {
public:
    explicit ProcNode(string procName) : TNode(TNodeType::TNODE_PROCEDURE, std::move(procName)) {}
};
