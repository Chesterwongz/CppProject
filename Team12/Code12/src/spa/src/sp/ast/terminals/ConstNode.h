#pragma once

#include "sp/ast/TNode.h"

class ConstNode : public TNode {
public:
    explicit ConstNode(string value):
        TNode(TNodeType::TNODE_CONST, std::move(value)) {}
};

