#pragma once

#include <string>
#include <vector>
#include "TNodeType.h"

class TNode {
private:
    std::string value;
    TNodeType type;
    std::vector<std::unique_ptr<TNode>> children;

public:
    explicit TNode(TNodeType type);
    TNode(TNodeType type, std::string value);
    virtual ~TNode() = default;
    void addChild(std::unique_ptr<TNode> child);
    std::string getValue();
    TNodeType getType();
    std::vector<TNode*> getChildren();
    [[nodiscard]] virtual bool isEqual(const TNode& other) const;
    friend bool operator==(const TNode& lhs, const TNode& rhs);
    friend bool operator!=(const TNode& lhs, const TNode& rhs);
};


