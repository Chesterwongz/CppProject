#include "TNode.h"

#include <utility>

TNode::TNode(TNodeType type, std::string value): type(type), value(std::move(value)) {}

void TNode::addChild(std::unique_ptr<TNode> child) {
    children.push_back(std::move(child));
}

std::string TNode::getValue() {
    return value;
}

TNodeType TNode::getType() {
    return type;
}

std::vector<TNode*> TNode::getChildren() {
    std::vector<TNode*> result;
    for (auto &child : children) {
        result.push_back(child.get());
    }
    return result;
}

TNode::TNode(TNodeType type) : type(type) {}
