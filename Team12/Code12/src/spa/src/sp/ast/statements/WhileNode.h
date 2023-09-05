#pragma once

#include "StmtNode.h"

class WhileNode : public StmtNode {
public:
    explicit WhileNode(int lineNum): StmtNode(TNodeType::TNODE_WHILE, "", lineNum) {}
};
