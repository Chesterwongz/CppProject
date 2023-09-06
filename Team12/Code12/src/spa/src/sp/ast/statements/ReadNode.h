#pragma once

#include "StmtNode.h"

class ReadNode : public StmtNode {
public:
    explicit ReadNode(int lineNum): StmtNode(TNodeType::TNODE_READ, "", lineNum) {}
};
