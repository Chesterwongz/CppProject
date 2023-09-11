#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "TNodeType.h"

using std::string, std::unique_ptr, std::vector;

class TNode {
private:
    string value;
    TNodeType type;
    vector<unique_ptr<TNode>> children;
protected:
    explicit TNode(TNodeType type);
    TNode(TNodeType type, string value);
public:
    virtual ~TNode() = default;
    void addChild(unique_ptr<TNode> child);
    string getValue();
    TNodeType getType();
    vector<TNode*> getChildren();
};


