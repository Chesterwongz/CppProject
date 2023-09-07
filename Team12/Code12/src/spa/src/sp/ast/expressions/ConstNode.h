#pragma once

#include "sp/ast/TNode.h"
#include "ExprNode.h"

class ConstNode : public ExprNode {
public:
    explicit ConstNode(std::string value): ExprNode(TNodeType::TNODE_CONST, std::move(value)) {}
    void accept(Extractor* e) const override;
};
