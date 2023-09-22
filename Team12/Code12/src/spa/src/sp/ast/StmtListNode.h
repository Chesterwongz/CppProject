#pragma once

#include <vector>
#include "TNode.h"
#include "sp/ast/statements/StmtNode.h"

class StmtListNode : public TNode {
public:
    StmtListNode(): TNode(TNodeType::TNODE_STMT_LIST) {}
    void accept(Extractor& e) const override;
    void cleanup(Extractor& e) const override;
    [[nodiscard]] std::vector<int> getChildrenLineNums() const;
    [[nodiscard]] int getStartLineNum() const;
};
