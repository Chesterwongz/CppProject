#include "FollowsStorage.h"

#include <iostream>
#include <vector>

// Constructor
FollowsStorage::FollowsStorage() {}

// Setter for follows relationship
void FollowsStorage::setFollows(int statementNumber, int followingStatement) {
    followsFrom[statementNumber].insert(followingStatement);
    followsTo[followingStatement].insert(statementNumber);
}

// Getter for all follows relationship
std::set<int> FollowsStorage::getAllFollows(int statementNumber) {
    if (followsFrom.find(statementNumber) == followsFrom.end()) {
        return {};
    }
    return followsFrom[statementNumber];
}

// Getter for all followed by relationship
std::set<int> FollowsStorage::getAllFollowedBy(int statementNumber) {
    if (followsTo.find(statementNumber) == followsTo.end()) {
        return {};
    }
    return followsTo[statementNumber];
}

// Getter for immediate follows relationship
int FollowsStorage::getImmediateFollows(int statementNumber) {
    if (followsFrom.find(statementNumber) == followsFrom.end()) {
        return -1;
    }
    return *(followsFrom[statementNumber].begin());
}

// Getter for immediate followed by relationship
int FollowsStorage::getImmediateFollowedBy(int statementNumber) {
    if (followsTo.find(statementNumber) == followsTo.end()) {
        return -1;
    }
    return *(followsTo[statementNumber].rbegin()); // Using rbegin() to get the largest element
}
