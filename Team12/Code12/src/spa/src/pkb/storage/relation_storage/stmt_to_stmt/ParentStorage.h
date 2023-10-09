#pragma once

#include <set>
#include <unordered_map>
#include <vector>
#include "pkb/interfaces/storage/relation_storage/IParentStorage.h"

class ParentStorage : public virtual IParentStorage {
 public:
  ParentStorage();

  // Setter for parent relationship
  void setParent(int statementNumber, int childStatement) override;

  // Setter for parent* relationship
  void setParentStar(int statementNumber, int childStatement) override;

  // Return all the immediate children of a particular statement
  std::set<int> getImmediateChildren(int statementNumber) override;

  // Return the immediate parent of a particular statmement
  int getImmediateParent(int statementNumber) override;

  // Return all children of a particular statement
  std::set<int> getAllChildren(int statementNumber) override;

  // Return all parents of a particular statement
  std::set<int> getAllParents(int statementNumber) override;

  // Return all statements that are parents of some statement in the program
  std::set<int> getAllParents();

  // Return all statements that are a children of some statement in the program
  std::set<int> getAllChildren();

 private:
  // (statement number -> immediate children statement numbers)
  std::unordered_map<int, std::set<int>> immediateChildrenOf;

  // (statement number -> all children statement numbers)
  std::unordered_map<int, std::set<int>> childrenOf;

  // (child statement number -> parents statement numbers)
  std::unordered_map<int, std::set<int>> parentsOf;
};
