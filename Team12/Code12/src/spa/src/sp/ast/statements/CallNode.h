#pragma once

#include "StmtNode.h"

class CallNode : public StmtNode {
public:
    explicit CallNode(int lineNum): StmtNode(TNodeType::TNODE_CALL, "", lineNum) {}
    void accept(Extractor* e) const override;
};
