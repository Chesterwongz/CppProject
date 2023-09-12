#pragma once

#include "StmtNode.h"

class AssignNode : public StmtNode {
public:
    explicit AssignNode(int lineNum): StmtNode(TNodeType::TNODE_ASSIGN, "", lineNum) {}
    void accept(Extractor* e) const override;
    void cleanup(Extractor* e) const override;
};
