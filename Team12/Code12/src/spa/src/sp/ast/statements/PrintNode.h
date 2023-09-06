#pragma once

#include "StmtNode.h"

class PrintNode : public StmtNode {
public:
    explicit PrintNode(int lineNum): StmtNode(TNodeType::TNODE_PRINT, "", lineNum) {}
};
