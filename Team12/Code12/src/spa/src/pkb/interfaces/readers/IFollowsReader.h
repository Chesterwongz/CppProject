#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"

class IFollowsReader {
 public:
  virtual ~IFollowsReader() = default;

  // return the statement number of the statement immediately following
  // statementNumber return s2 that satisfies Follows(s1, s2) and is of same
  // type as statementType
  virtual std::string getFollowing(int statementNumber,
                                   StmtType statementType) = 0;

  // return the statement number of the statement that statementNumber
  // immediately follows return s1 that satisfies Follows(s1, s2) and is of same
  // type as statementType
  virtual std::string getFollowed(int statementNumber,
                                  StmtType statementType) = 0;

  // return true if Follows(statementNumber, followingStatement) holds and false
  // otherwise
  virtual bool isFollows(int statementNumber, int followingStatement) = 0;

  // return all pairs (s1,s2) that satisfy Follows(s1, s2) and satisfying
  // statement type restriction
  virtual std::vector<std::pair<std::string, std::string>> getFollowsPairs(
      StmtType statementType1, StmtType statementType2) = 0;

  // return all pairs (s1, s2) that satisfy Follows*(s1, s2) where s2 is of same
  // type as statementType and s1 is statementNumber
  virtual std::vector<std::pair<std::string, std::string>> getFollowsStar(
      int statementNumber, StmtType statementType) = 0;

  // return all pairs (s1, s2) that satisfy Follows*(s1, s2) where s1 is of same
  // type as statementType and s2 is statementNumber
  virtual std::vector<std::pair<std::string, std::string>> getFollowedStar(
      int statementNumber, StmtType statementType) = 0;

  // return true if Follows*(statementNumber, followingStatement) holds and
  // false otherwise
  virtual bool isFollowsStar(int statementNumber, int followingStatement) = 0;

  // return all pairs (s1,s2) that satisfy Follows*(s1, s2) and satisfying
  // statement type restriction
  virtual std::vector<std::pair<std::string, std::string>> getFollowsStarPairs(
      StmtType statementType1, StmtType statementType2) = 0;
};
