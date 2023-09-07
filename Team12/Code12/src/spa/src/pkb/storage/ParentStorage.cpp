#include "ParentStorage.h"

#include <iostream>
#include <vector>
#include <map>

// Constructor
ParentStorage::ParentStorage() {}

// Setter for parent relationship
void ParentStorage::setParent(int statementNumber, int childStatement) {
    // Set in parentOf storage
    if (!parentOf.count(statementNumber)) {
        parentOf[statementNumber] = std::vector<int>{ childStatement };
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
        childOf[childStatement] = std::vector<int>{ statementNumber };
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
std::vector<int> ParentStorage::getAllChildren(int statementNumber) {
    if (parentOf.count(statementNumber)) {
        return parentOf[statementNumber];
    }
    else {
        return std::vector<int>();
    }
}

// Getter for all parents relationship
std::vector<int> ParentStorage::getAllParents(int statementNumber) {
    if (childOf.count(statementNumber)) {
        return childOf[statementNumber];
    }
    else {
        return std::vector<int>();
    }
}

// Getter for immediate child relationship
int ParentStorage::getImmediateChild(int statementNumber) {
    if (parentOf.count(statementNumber) && !parentOf[statementNumber].empty()) {
        return parentOf[statementNumber][0]; // Since the vector is sorted, first element is the smallest
    }
    else {
        return -1; // Return -1 if there are no immediate children
    }
}

// Getter for immediate parent relationship
int ParentStorage::getImmediateParent(int statementNumber) {
    if (childOf.count(statementNumber) && !childOf[statementNumber].empty()) {
        const auto& vec = childOf[statementNumber];
        return vec[vec.size() - 1]; // Last element is the largest in a sorted vector
    }
    else {
        return -1; // Return -1 if there are no immediate parents
    }
}

// Data structure for parent relationship (statement number -> child statement numbers)
std::map<int, std::vector<int>> parentOf;

// Data structure for child relationship (child statement number -> parent statement numbers)
std::map<int, std::vector<int>> childOf;
