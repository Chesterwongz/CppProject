#include "TNode.h"

#include <iostream>
#include <utility>

TNode::TNode(TNodeType type): type(type) {}

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

bool TNode::isEqual(const TNode &other) const {
    if (this == &other) {
        return true;
    }

    if (type != other.type || value != other.value) {
        return false;
    }

    if (children.size() != other.children.size()) {
        return false;
    }

    for (size_t i = 0; i < children.size(); i++) {
        if (!children[i]->isEqual(*other.children[i])) {
            return false;
        }
    }
    return true;
}

bool operator==(const TNode& lhs, const TNode& rhs) {
    return lhs.isEqual(rhs);
}

bool operator!=(const TNode& lhs, const TNode& rhs) {
    return !(lhs == rhs);
}

