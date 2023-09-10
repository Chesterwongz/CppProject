#include "ParentStorage.h"

#include <iostream>
#include <unordered_map>
#include <set>

// Constructor
ParentStorage::ParentStorage() {}

// Setter for parent relationship
void ParentStorage::setParent(int statementNumber, int childStatement) {
    // Set in parentOf storage
    if (!parentOf.count(statementNumber)) {
        parentOf[statementNumber] = std::set<int>{ childStatement };
    }
    else {
        auto& vec = parentOf[statementNumber];
        auto it = std::lower_bound(vec.begin(), vec.end(), childStatement);
        if (it == vec.end() || *it != childStatement) {
            vec.insert(it, childStatement);
        }
    }

    // Set in childOf storage
    if (!childOf.count(childStatement)) {
        childOf[childStatement] = std::set<int>{ statementNumber };
    }
    else {
        auto& vec = childOf[childStatement];
        auto it = std::lower_bound(vec.begin(), vec.end(), statementNumber);
        if (it == vec.end() || *it != statementNumber) {
            vec.insert(it, statementNumber);
        }
    }
}

// Getter for all children relationship
std::set<int> ParentStorage::getAllChildren(int statementNumber) {
    if (parentOf.count(statementNumber)) {
        return parentOf[statementNumber];
    }
    else {
        return std::set<int>();
    }
}

// Getter for all parents relationship
std::set<int> ParentStorage::getAllParents(int statementNumber) {
    if (childOf.count(statementNumber)) {
        return childOf[statementNumber];
    }
    else {
        return std::set<int>();
    }
}

// Getter for immediate child relationship
int ParentStorage::getImmediateChild(int statementNumber) {
    if (parentOf.count(statementNumber) && !parentOf[statementNumber].empty()) {
        return *parentOf[statementNumber].begin(); // Use begin() to get the first element of the set
    }
    else {
        return -1; // Return -1 if there are no immediate children
    }
}

// Getter for immediate parent relationship
int ParentStorage::getImmediateParent(int statementNumber) {
    if (childOf.count(statementNumber) && !childOf[statementNumber].empty()) {
        return *childOf[statementNumber].begin(); // Use begin() to get the first element of the set
    }
    else {
        return -1; // Return -1 if there are no immediate parents
    }
}

