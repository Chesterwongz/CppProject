#include "ParentStorage.h"

#include <iostream>
#include <unordered_map>
#include <set>

// Constructor
ParentStorage::ParentStorage() = default;

// Setter for parent relationship
void ParentStorage::setParent(int statementNumber, int childStatement) {
    childrenOf[statementNumber].insert(childStatement);
    parentsOf[childStatement].insert(statementNumber);
}

// Getter for all children relationship
std::set<int> ParentStorage::getAllChildren(int statementNumber) {
    if (childrenOf.find(statementNumber) == childrenOf.end()) {
        return {};
    }
    return childrenOf[statementNumber];
}

// Getter for all parents relationship
std::set<int> ParentStorage::getAllParents(int statementNumber) {
    if (parentsOf.find(statementNumber) == parentsOf.end()) {
        return {};
    }
    return parentsOf[statementNumber];
}

// Getter for all parents
std::set<int> ParentStorage::getAllParents() {
    std::set<int> allParents;
    for (const auto& entry : childrenOf) {
        allParents.insert(entry.first);
    }
    return allParents;
}

// Getter for all children
std::set<int> ParentStorage::getAllChildren() {
    std::set<int> allChildren;
    for (const auto& entry : parentsOf) {
        allChildren.insert(entry.first);
    }
    return allChildren;
}

// Getter for immediate children relationship - 1 parent can have multiple children with varying line numbers
std::set<int> ParentStorage::getImmediateChildren(int statementNumber) {
    if (childrenOf.find(statementNumber) == childrenOf.end()) {
        return {};
    }
    std::set<int> immediateChildren = childrenOf[statementNumber];
    for (int child : childrenOf[statementNumber]) {
        if (childrenOf.find(child) != childrenOf.end()) {
            for (int grandChild : childrenOf[child]) {
                immediateChildren.erase(grandChild);
            }
        }
    }

    return immediateChildren;
}

// Getter for immediate parent relationship - largest statement number
int ParentStorage::getImmediateParent(int statementNumber) {
    if (parentsOf.find(statementNumber) == parentsOf.end()) {
        return -1;
    }
    return *parentsOf[statementNumber].rbegin();
}

