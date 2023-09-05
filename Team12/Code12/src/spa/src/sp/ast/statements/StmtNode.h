#pragma once


#include <utility>

#include "sp/ast/TNode.h"

class StmtNode : public TNode {
private:
    int lineNum;

public:
    explicit StmtNode(TNodeType type, std::string value, int lineNum) : TNode(type, std::move(value)),  lineNum(lineNum) {}
    virtual ~StmtNode() = default;
    [[nodiscard]] int getLineNum() const;
};

