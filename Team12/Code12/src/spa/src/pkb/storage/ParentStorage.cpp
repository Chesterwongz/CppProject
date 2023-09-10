#include "ParentStorage.h"

#include <iostream>
#include <unordered_map>
#include <set>

// Constructor
ParentStorage::ParentStorage() {}

// Setter for parent relationship
void ParentStorage::setParent(int statementNumber, int childStatement) {
    // Set in parentOf storage
    parentOf[statementNumber].insert(childStatement);

    // Set in childOf storage
    childOf[childStatement].insert(statementNumber);
}

// Getter for all children relationship
std::set<int> ParentStorage::getAllChildren(int statementNumber) {
    return parentOf[statementNumber];
}

// Getter for all parents relationship
std::set<int> ParentStorage::getAllParents(int statementNumber) {
    return childOf[statementNumber];
}

// Getter for immediate child relationship
int ParentStorage::getImmediateChild(int statementNumber) {
    if (!parentOf[statementNumber].empty()) {
        return *parentOf[statementNumber].begin(); // Use begin() to get the first element of the set
    }
    else {
        return -1; // Return -1 if there are no immediate children
    }
}

// Getter for immediate parent relationship
int ParentStorage::getImmediateParent(int statementNumber) {
    if (!childOf[statementNumber].empty()) {
        return *childOf[statementNumber].begin(); // Use begin() to get the first element of the set
    }
    else {
        return -1; // Return -1 if there are no immediate parents
    }
}

