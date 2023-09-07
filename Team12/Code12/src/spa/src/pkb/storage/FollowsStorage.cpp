#include "FollowsStorage.h"

#include <iostream>
#include <vector>
#include <map>

// Constructor
FollowsStorage::FollowsStorage() {}

// Setter for follows relationship
void FollowsStorage::setFollows(int statementNumber, int followingStatement) {
    if (!followsFrom.count(statementNumber)) {
        followsFrom[statementNumber] = std::vector<int>{ followingStatement };
    }
    else {
        auto& vec = followsFrom[statementNumber];
        auto it = std::lower_bound(vec.begin(), vec.end(), followingStatement);
        if (it == vec.end() || *it != followingStatement) {
            vec.insert(it, followingStatement);
        }
    }

    if (!followsTo.count(followingStatement)) {
        followsTo[followingStatement] = std::vector<int>{ statementNumber };
    }
    else {
        auto& vec = followsTo[followingStatement];
        auto it = std::lower_bound(vec.begin(), vec.end(), statementNumber);
        if (it == vec.end() || *it != statementNumber) {
            vec.insert(it, statementNumber);
        }
    }
}

// Getter for all follows relationship
std::vector<int> FollowsStorage::getAllFollows(int statementNumber) {
    if (followsFrom.count(statementNumber)) {
        return followsFrom[statementNumber];
    }
    else {
        return std::vector<int>();
    }
}

// Getter for all followed by relationship
std::vector<int> FollowsStorage::getAllFollowedBy(int statementNumber) {
    if (followsTo.count(statementNumber)) {
        return followsTo[statementNumber];
    }
    else {
        return std::vector<int>();
    }
}

// Getter for immediate follows relationship
int FollowsStorage::getImmediateFollows(int statementNumber) {
    if (followsFrom.count(statementNumber) && !followsFrom[statementNumber].empty()) {
        return followsFrom[statementNumber][0]; // Since the vector is sorted, first element is the smallest
    }
    else {
        return -1; // Return -1 if there are no immediate follows
    }
}

// Getter for immediate followed by relationship
int FollowsStorage::getImmediateFollowedBy(int statementNumber) {
    if (followsTo.count(statementNumber) && !followsTo[statementNumber].empty()) {
        const auto& vec = followsTo[statementNumber];
        return vec[vec.size() - 1]; // Last element is the largest in a sorted vector
    }
    else {
        return -1; // Return -1 if there are no immediate followed by
    }
}


// Data structure for follows relationship (statement number -> following statement numbers)
std::map<int, std::vector<int>> followsFrom;

// Data structure for followed by relationship (following statement number -> statement numbers)
std::map<int, std::vector<int>> followsTo;

