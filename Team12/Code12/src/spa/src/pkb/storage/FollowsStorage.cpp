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
    return std::set<int>(followsFrom[statementNumber].begin(), followsFrom[statementNumber].end());
}

// Getter for all followed by relationship
std::set<int> FollowsStorage::getAllFollowedBy(int statementNumber) {
    return std::set<int>(followsTo[statementNumber].begin(), followsTo[statementNumber].end());
}

// Getter for immediate follows relationship
int FollowsStorage::getImmediateFollows(int statementNumber) {
    if (followsFrom.count(statementNumber) && !followsFrom[statementNumber].empty()) {
        return *(followsFrom[statementNumber].begin());
    }
    else {
        return -1;
    }
}

// Getter for immediate followed by relationship
int FollowsStorage::getImmediateFollowedBy(int statementNumber) {
    if (followsTo.count(statementNumber) && !followsTo[statementNumber].empty()) {
        return *(followsTo[statementNumber].rbegin()); // Using rbegin() to get the largest element
    }
    else {
        return -1;
    }
}
