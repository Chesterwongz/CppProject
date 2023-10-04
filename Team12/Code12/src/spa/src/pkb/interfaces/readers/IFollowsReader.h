#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"

class IFollowsReader {
 public:
  virtual std::string getFollowing(int statementNumber,
                                   StmtType statementType) = 0;
  virtual std::string getFollowed(int statementNumber,
                                  StmtType statementType) = 0;
  virtual bool isFollows(int statementNumber, int followingStatement) = 0;
  virtual std::vector<std::pair<std::string, std::string>> getFollowsPairs(
      StmtType statementType1, StmtType statementType2) = 0;
  virtual std::vector<std::pair<std::string, std::string>> getFollowsStar(
      int statementNumber, StmtType statementType) = 0;
  virtual std::vector<std::pair<std::string, std::string>> getFollowedStar(
      int statementNumber, StmtType statementType) = 0;
  virtual bool isFollowsStar(int statementNumber, int followingStatement) = 0;
  virtual std::vector<std::pair<std::string, std::string>> getFollowsStarPairs(
      StmtType statementType1, StmtType statementType2) = 0;
};
