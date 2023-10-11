#include "ParentStorage.h"

void ParentStorage::setParent(int statementNumber, int childStatement) {
  immediateSuccessorMap[statementNumber].insert(childStatement);
  ancestorMap[childStatement].insert(statementNumber);
}

void ParentStorage::setParentStar(int statementNumber, int childStatement) {
  successorMap[statementNumber].insert(childStatement);
  ancestorMap[childStatement].insert(statementNumber);
}

std::set<int> ParentStorage::getAllChildren(int statementNumber) {
  if (successorMap.find(statementNumber) == successorMap.end()) {
    return {};
  }
  return successorMap[statementNumber];
}

std::set<int> ParentStorage::getAllParents(int statementNumber) {
  if (ancestorMap.find(statementNumber) == ancestorMap.end()) {
    return {};
  }
  return ancestorMap[statementNumber];
}

std::set<int> ParentStorage::getAllParents() {
  std::set<int> allParents;
  for (const auto& entry : successorMap) {
    allParents.insert(entry.first);
  }
  return allParents;
}

std::set<int> ParentStorage::getAllChildren() {
  std::set<int> allChildren;
  for (const auto& entry : ancestorMap) {
    allChildren.insert(entry.first);
  }
  return allChildren;
}

std::set<int> ParentStorage::getImmediateChildren(int statementNumber) {
  if (immediateSuccessorMap.find(statementNumber) ==
      immediateSuccessorMap.end()) {
    return {};
  }
  return immediateSuccessorMap[statementNumber];
}

int ParentStorage::getImmediateParent(int statementNumber) {
  if (ancestorMap.find(statementNumber) == ancestorMap.end()) {
    return -1;
  }
  return *ancestorMap[statementNumber].rbegin();
}
