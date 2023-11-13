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

  std::vector<std::string> getImmediateChildrenOf(int s1,
                                                  StmtType type2) override {
    if (s1 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockParentChildPairs.size());
      for (auto &pair : mockParentChildPairs) {
        res.push_back(pair.second);
      }
      return res;
    } else {
      return mockImmediateChildrenOf;
    }
  }

  std::vector<std::string> getImmediateParentOf(int s2,
                                                StmtType type1) override {
    if (s2 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockParentChildPairs.size());
      for (auto &pair : mockParentChildPairs) {
        res.push_back(pair.first);
      }
      return res;
    } else {
      return mockImmediateParentOf;
    }
  }

  vector<pair<string, string>> getParentChildPairs(
      StmtType parentType, StmtType childType) override {
    return mockParentChildPairs;
  }

  std::vector<std::string> getChildrenStarOf(int s1, StmtType type2) override {
    if (s1 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockParentChildStarPairs.size());
      for (auto &pair : mockParentChildStarPairs) {
        res.push_back(pair.second);
      }
      return res;
    } else {
      return mockChildrenStar;
    }
  }

  std::vector<std::string> getParentStarOf(int s2, StmtType type1) override {
    if (s2 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockParentChildStarPairs.size());
      for (auto &pair : mockParentChildStarPairs) {
        res.push_back(pair.first);
      }
      return res;
    } else {
      return mockParentStarOf;
    }
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
