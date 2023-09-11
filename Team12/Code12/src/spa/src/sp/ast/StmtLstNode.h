#pragma once

#include "TNode.h"

class StmtLstNode : public TNode {
public:
    explicit StmtLstNode() : TNode(TNodeType::TNODE_STMT_LIST) {}
};
