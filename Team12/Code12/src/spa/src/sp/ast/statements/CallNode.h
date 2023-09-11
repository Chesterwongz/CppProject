#pragma once

#include "StmtNode.h"

class CallNode : public StmtNode {
public:
    explicit CallNode(std::string procName, int lineNum)
        : StmtNode(TNodeType::TNODE_CALL, std::move(procName), lineNum) {}
};
