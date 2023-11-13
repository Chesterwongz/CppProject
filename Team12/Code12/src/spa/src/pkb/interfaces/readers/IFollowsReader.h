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
  // stmt return s2 that satisfies Follows(s1, s2) and is of same
  // type as stmtType
  virtual std::vector<std::string> getFollowing(int s1, StmtType type2) = 0;

  // return the statement number of the statement that stmt
  // immediately follows return s1 that satisfies Follows(s1, s2) and is of same
  // type as stmtType
  virtual std::vector<std::string> getFollowed(int s2, StmtType type1) = 0;

  // return true if Follows(stmt1, stmt2) holds and false
  // otherwise
  virtual bool isFollows(int stmt1, int stmt2) = 0;

  // return all pairs (s1,s2) that satisfy Follows(s1, s2) and satisfying
  // statement type restriction
  virtual std::vector<std::pair<std::string, std::string>> getFollowsPairs(
      StmtType stmtTYpe1, StmtType stmtType2) = 0;

  // return all pairs (s1, s2) that satisfy Follows*(s1, s2) where s2 is of same
  // type as stmtType and s1 is stmt
  virtual std::vector<std::string> getFollowsStar(int s1, StmtType type2) = 0;

  // return all pairs (s1, s2) that satisfy Follows*(s1, s2) where s1 is of same
  // type as stmtType and s2 is stmt
  virtual std::vector<std::string> getFollowedStar(int s2, StmtType type1) = 0;

  // return true if Follows*(stmt1, stmt2) holds and
  // false otherwise
  virtual bool isFollowsStar(int stmt1, int stmt2) = 0;

  // return all pairs (s1,s2) that satisfy Follows*(s1, s2) and satisfying
  // statement type restriction
  virtual std::vector<std::pair<std::string, std::string>> getFollowsStarPairs(
      StmtType stmtType1, StmtType stmtType2) = 0;
};
