#pragma once

#include "TNode.h"

class StmtListNode : public TNode {
public:
    StmtListNode(): TNode(TNodeType::TNODE_STMT_LIST) {}
};
