#include "TNode.h"

#include <utility>

TNode::TNode(TNodeType type) : type(type) {}
TNode::TNode(TNodeType type, string value): type(type), value(std::move(value)) {}

void TNode::addChild(unique_ptr<TNode> child) {
    children.push_back(std::move(child));
}

std::string TNode::getValue() {
    return value;
}

TNodeType TNode::getType() {
    return type;
}

vector<TNode*> TNode::getChildren() {
    vector<TNode*> result;
    result.reserve(children.size());
    for (auto &child : children) {
        result.push_back(child.get());
    }
    return result;
}

