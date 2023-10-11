#include "ParentStorage.h"

ParentStorage::ParentStorage() = default;

void ParentStorage::setParent(int statementNumber, int childStatement) {
  immediateChildrenOf[statementNumber].insert(childStatement);
  parentsOf[childStatement].insert(statementNumber);
}

void ParentStorage::setParentStar(int statementNumber, int childStatement) {
  childrenOf[statementNumber].insert(childStatement);
  parentsOf[childStatement].insert(statementNumber);
}

std::set<int> ParentStorage::getAllChildren(int statementNumber) {
  if (childrenOf.find(statementNumber) == childrenOf.end()) {
    return {};
  }
  return childrenOf[statementNumber];
}

std::set<int> ParentStorage::getAllParents(int statementNumber) {
  if (parentsOf.find(statementNumber) == parentsOf.end()) {
    return {};
  }
  return parentsOf[statementNumber];
}

std::set<int> ParentStorage::getAllParents() {
  std::set<int> allParents;
  for (const auto& entry : childrenOf) {
    allParents.insert(entry.first);
  }
  return allParents;
}

std::set<int> ParentStorage::getAllChildren() {
  std::set<int> allChildren;
  for (const auto& entry : parentsOf) {
    allChildren.insert(entry.first);
  }
  return allChildren;
}

std::set<int> ParentStorage::getImmediateChildren(int statementNumber) {
  if (immediateChildrenOf.find(statementNumber) == immediateChildrenOf.end()) {
    return {};
  }
  return immediateChildrenOf[statementNumber];
}

int ParentStorage::getImmediateParent(int statementNumber) {
  if (parentsOf.find(statementNumber) == parentsOf.end()) {
    return -1;
  }
  return *parentsOf[statementNumber].rbegin();
}
