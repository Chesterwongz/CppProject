#include "FollowsStorage.h"

// Setter for follows relationship
void FollowsStorage::setFollows(int statementNumber, int followingStatement) {
  successorMap[statementNumber].insert(followingStatement);
  ancestorMap[followingStatement].insert(statementNumber);
}

// Getter for all follows relationship
std::set<int> FollowsStorage::getAllFollows(int statementNumber) {
  if (successorMap.find(statementNumber) == successorMap.end()) {
    return {};
  }
  return successorMap[statementNumber];
}

// Getter for all followed by relationship
std::set<int> FollowsStorage::getAllFollowedBy(int statementNumber) {
  if (ancestorMap.find(statementNumber) == ancestorMap.end()) {
    return {};
  }
  return ancestorMap[statementNumber];
}

// Getter for immediate follows relationship
int FollowsStorage::getImmediateFollows(int statementNumber) {
  if (successorMap.find(statementNumber) == successorMap.end()) {
    return -1;
  }
  return *(successorMap[statementNumber].begin());
}

// Getter for immediate followed by relationship
int FollowsStorage::getImmediateFollowedBy(int statementNumber) {
  if (ancestorMap.find(statementNumber) == ancestorMap.end()) {
    return -1;
  }
  return *(ancestorMap[statementNumber].rbegin());
}
