#pragma once

#include "StmtNode.h"

class AssignNode : public StmtNode {
public:
    explicit AssignNode(int lineNum): StmtNode(TNodeType::TNODE_ASSIGN, "", lineNum) {}
};
