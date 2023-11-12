#pragma once

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "BaseMockReader.h"
#include "pkb/facade/PKBReader.h"

using std::vector, std::set, std::string, std::pair;

class MockParentsReader : public BaseMockReader {
 public:
  vector<string> mockImmediateChildrenOf;
  vector<string> mockImmediateParentOf;
  vector<pair<string, string>> mockParentChildPairs;
  vector<string> mockChildrenStar;
  vector<string> mockParentStarOf;
  vector<pair<string, string>> mockParentChildStarPairs;
  bool mockIsParentStar {};
  bool mockIsParent {};

  MockParentsReader() : BaseMockReader() {}

  std::vector<std::string> getImmediateChildrenOf(
      int statementNumber, StmtType statementType) override {
    return mockImmediateChildrenOf;
  }

  std::vector<std::string> getImmediateParentOf(
      int statementNumber, StmtType statementType) override {
    return mockImmediateParentOf;
  }

  vector<pair<string, string>> getParentChildPairs(
      StmtType parentType, StmtType childType) override {
    return mockParentChildPairs;
  }

  std::vector<std::string> getChildrenStarOf(int statementNumber,
                                             StmtType statementType) override {
    return mockChildrenStar;
  }

  std::vector<std::string> getParentStarOf(int statementNumber,
                                           StmtType statementType) override {
    return mockParentStarOf;
  }

  vector<pair<string, string>> getParentChildStarPairs(
      StmtType parentType, StmtType childType) override {
    return mockParentChildStarPairs;
  }

  bool isParent(int statementNumber, int followingStatement) override {
    return mockIsParent;
  }

  bool isParentStar(int statementNumber, int followingStatement) override {
    return mockIsParentStar;
  }

  bool hasParents() override { return !mockParentChildPairs.empty(); }

  bool hasParentsT() override { return !mockParentChildStarPairs.empty(); }
};
