#pragma once

#include "TNode.h"

class StmtListNode : public TNode {
public:
    StmtListNode(): TNode(TNodeType::TNODE_STMT_LIST) {}
    void accept(Extractor* e) const override;
    void reject(Extractor* e) const override;
};
