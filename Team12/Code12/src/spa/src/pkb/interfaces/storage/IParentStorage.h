#pragma once

#include <set>

class IParentStorage {
 public:
  virtual ~IParentStorage() = default;

  virtual void setParent(int statementNumber, int childStatement) = 0;
  virtual void setParentStar(int statementNumber, int childStatement) = 0;

  virtual std::set<int> getImmediateChildren(int statementNumber) = 0;
  virtual int getImmediateParent(int statementNumber) = 0;

  virtual std::set<int> getAllChildren(int statementNumber) = 0;
  virtual std::set<int> getAllParents(int statementNumber) = 0;
};
