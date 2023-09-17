#include "TNode.h"

TNode::TNode(TNodeType type) : type(type) {}

TNode::TNode(TNodeType type, string value): type(type), value(std::move(value)) {}

void TNode::addChild(unique_ptr<TNode> child) {
    children.push_back(std::move(child));
}

std::string TNode::getValue() const {
    return value;
}

TNodeType TNode::getType() const {
    return type;
}

TNode * TNode::getChildAt(int index) const {
    if (index < 0 || index >= children.size()) {
        return nullptr;
    }
    return children.at(index).get();
}

string TNode::getChildValueAt(int index) const {
    if (index < 0 || index >= children.size()) {
        return "";
    }
    return children.at(index)->getValue();
}

vector<TNode*> TNode::getChildren() const {
    vector<TNode*> result;
    result.reserve(children.size());
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

void TNode::accept(Extractor *e) const {}

void TNode::cleanup(Extractor *e) const {}
