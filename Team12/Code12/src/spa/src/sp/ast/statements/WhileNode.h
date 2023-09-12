#pragma once

#include "StmtNode.h"

class WhileNode : public StmtNode {
public:
    explicit WhileNode(int lineNum): StmtNode(TNodeType::TNODE_WHILE, "", lineNum) {}
    void accept(Extractor* e) const override;
    void cleanup(Extractor* e) const override;
};
