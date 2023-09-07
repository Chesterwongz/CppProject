#pragma once

#include "sp/ast/TNode.h"
#include "ExprNode.h"

class VarNode : public ExprNode {
public:
    explicit VarNode(std::string name): ExprNode(TNodeType::TNODE_CONST, std::move(name)) {}
    void accept(Extractor* e) const override;
};
