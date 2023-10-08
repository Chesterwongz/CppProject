#pragma once

#include <set>

class IFollowsStorage {
 public:
  virtual ~IFollowsStorage() = default;

  virtual void setFollows(int statementNumber, int followingStatement) = 0;

  virtual int getImmediateFollows(int statementNumber) = 0;
  virtual int getImmediateFollowedBy(int statementNumber) = 0;

  virtual std::set<int> getAllFollows(int statementNumber) = 0;
  virtual std::set<int> getAllFollowedBy(int statementNumber) = 0;
};