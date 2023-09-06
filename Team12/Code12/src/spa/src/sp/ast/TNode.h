#pragma once

#include <string>
#include <vector>
#include <memory>
#include "TNodeType.h"

class TNode {
private:
    std::string value;
    TNodeType type;
    std::vector<std::unique_ptr<TNode>> children;

public:
    explicit TNode(TNodeType type);
    TNode(TNodeType type, std::string value);
    ~TNode() = default;
    void addChild(std::unique_ptr<TNode> child);
    std::string getValue();
    TNodeType getType();
    std::vector<TNode*> getChildren();
};


