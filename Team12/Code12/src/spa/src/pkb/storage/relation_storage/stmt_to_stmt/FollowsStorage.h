#pragma once

#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

#include "pkb/interfaces/storage/relation_storage/IFollowsStorage.h"

class FollowsStorage : public IFollowsStorage {
 private:
  // (statement number -> following statement numbers)
  std::unordered_map<int, std::set<int>> successorMap;

  // (following statement number -> statement numbers)
  std::unordered_map<int, std::set<int>> ancestorMap;

 public:
  // Setter for follows* relationship
  void setFollows(int statementNumber, int followingStatement) override;

  // Return s2 that satisfies Follows(s1, s2) where s1 is statementNumber
  int getImmediateFollows(int statementNumber) override;

  // Return s1 that satisfies Follows(s1, s2) where s2 is statementNumber
  int getImmediateFollowedBy(int statementNumber) override;

  // Return all s2 that satisfies Follows*(s1, s2) where s1 is statementNumber
  std::set<int> getAllFollows(int statementNumber) override;

  // Return all s1 that satisfies Follows*(s1, s2) where s2 is statementNumber
  std::set<int> getAllFollowedBy(int statementNumber) override;
};
