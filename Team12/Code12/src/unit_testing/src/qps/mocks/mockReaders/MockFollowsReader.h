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

  std::vector<std::string> getFollowing(int statementNumber,
                                        StmtType statementType) override {
    return mockFollowing;
  }

  std::vector<std::string> getFollowed(int statementNumber,
                                       StmtType statementType) override {
    return mockFollowed;
  }

  vector<pair<string, string>> getFollowsPairs(
      StmtType statementType1, StmtType statementType2) override {
    return mockFollowsPairs;
  }

  std::vector<std::string> getFollowsStar(int statementNumber,
                                          StmtType statementType) override {
    return mockFollowsStar;
  }

  std::vector<std::string> getFollowedStar(int statementNumber,
                                           StmtType statementType) override {
    return mockFollowedStar;
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
