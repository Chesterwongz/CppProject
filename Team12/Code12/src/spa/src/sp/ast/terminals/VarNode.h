#pragma once

#include "sp/ast/TNode.h"

class VarNode : public TNode {
public:
    explicit VarNode(string value): TNode(TNodeType::TNODE_VAR, std::move(value)) {}
    void accept(Extractor* e) const override;
};

