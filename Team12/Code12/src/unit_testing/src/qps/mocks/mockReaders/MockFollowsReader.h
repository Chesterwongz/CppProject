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
#include "pkb/facade/PKBStore.h"

using std::vector, std::set, std::string, std::pair;

class MockFollowsReader : public BaseMockReader {
 public:
  vector<string> mockFollowing;
  vector<string> mockFollowed;
  vector<pair<string, string>> mockFollowsPairs;
  vector<string> mockFollowsStar;
  vector<string> mockFollowedStar;
  vector<pair<string, string>> mockFollowedPairs;
  vector<pair<string, string>> mockFollowsStarPairs;
  bool mockIsFollowsStar {};
  bool mockIsFollows {};

  MockFollowsReader() : BaseMockReader() {}

  std::vector<std::string> getFollowing(int s1, StmtType type2) override {
    if (s1 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockFollowsPairs.size());
      for (auto &pair : mockFollowsPairs) {
        res.push_back(pair.second);
      }
      return res;
    } else {
      return mockFollowing;
    }
  }

  std::vector<std::string> getFollowed(int s2, StmtType type1) override {
    if (s2 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockFollowsPairs.size());
      for (auto &pair : mockFollowsPairs) {
        res.push_back(pair.first);
      }
      return res;
    } else {
      return mockFollowed;
    }
  }

  vector<pair<string, string>> getFollowsPairs(
      StmtType statementType1, StmtType statementType2) override {
    return mockFollowsPairs;
  }

  std::vector<std::string> getFollowsStar(int s1, StmtType type2) override {
    if (s1 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockFollowsStarPairs.size());
      for (auto &pair : mockFollowsStarPairs) {
        res.push_back(pair.second);
      }
      return res;
    } else {
      return mockFollowsStar;
    }
  }

  std::vector<std::string> getFollowedStar(int s2, StmtType type1) override {
    if (s2 == common::WILDCARD_STMT_NUM) {
      vector<string> res;
      res.reserve(mockFollowsStarPairs.size());
      for (auto &pair : mockFollowsStarPairs) {
        res.push_back(pair.first);
      }
      return res;
    } else {
      return mockFollowedStar;
    }
  }

  vector<pair<string, string>> getFollowsStarPairs(
      StmtType statementType1, StmtType statementType2) override {
    return mockFollowsStarPairs;
  }

  bool isFollows(int statementNumber, int followingStatement) override {
    return mockIsFollows;
  }

  bool isFollowsStar(int statementNumber, int followingStatement) override {
    return mockIsFollowsStar;
  }

  bool hasFollows() override { return !mockFollowsPairs.empty(); }

  bool hasFollowsT() override { return !mockFollowsStarPairs.empty(); }
};
