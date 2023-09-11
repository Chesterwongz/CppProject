#include "ParentStorage.h"

#include <iostream>
#include <unordered_map>
#include <set>

// Constructor
ParentStorage::ParentStorage() = default;

// Setter for parent relationship
void ParentStorage::setParent(int statementNumber, int childStatement) {
    // Set in parentOf storage
    parentOf[statementNumber].insert(childStatement);

    // Set in childOf storage
    childOf[childStatement].insert(statementNumber);
}

// Getter for all children relationship
std::unordered_set<int> ParentStorage::getAllChildren(int statementNumber) {
    if (parentOf.find(statementNumber) == parentOf.end()) {
        return {};
    }
    return parentOf[statementNumber];
}

// Getter for all parents relationship
std::set<int> ParentStorage::getAllParents(int statementNumber) {
    if (childOf.find(statementNumber) == childOf.end()) {
        return {};
    }
    return childOf[statementNumber];
}

// Getter for immediate children relationship - 1 parent can have multiple children with varying line numbers
std::unordered_set<int> ParentStorage::getImmediateChildren(int statementNumber) {
    if (parentOf.find(statementNumber) == parentOf.end()) {
        return {};
    }
    std::unordered_set<int> immediateChildren = parentOf[statementNumber];
    for (int child : immediateChildren) {
        if (parentOf.find(child) != parentOf.end()) {
            immediateChildren.erase(child);
        }
    }

    return immediateChildren;
}

// Getter for immediate parent relationship - largest statement number
int ParentStorage::getImmediateParent(int statementNumber) {
    if (childOf.find(statementNumber) == childOf.end()) {
        return -1;
    }
    return *childOf[statementNumber].rbegin(); // Use begin() to get the first element of the set
}

