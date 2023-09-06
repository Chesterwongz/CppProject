#pragma once


#include <utility>

#include "sp/ast/TNode.h"

class StmtNode : public TNode {
private:
    int lineNum;

public:
    explicit StmtNode(TNodeType type, std::string value, int lineNum) :
        TNode(type, std::move(value)),  lineNum(lineNum) {}
    [[nodiscard]] int getLineNum() const;
    [[nodiscard]] bool isEqual(const TNode& other) const override;
};

