#pragma once

#include <string>
#include <utility>
#include <vector>

#include "common/StmtTypes.h"

class IParentReader {
 public:
  virtual ~IParentReader() = default;

  // return all pairs (s1, s2) that satisfy Parent(s1, s2) where s2 is of same
  // type as statementType and s1 is statementNumber
  virtual std::vector<std::string> getImmediateChildrenOf(
      int statementNumber, StmtType statementType) = 0;

  // return a pair (s1, s2) that satisfy Parent(s1, s2) where s1 is of same type
  // as statementType and s2 is statementNumber
  virtual std::vector<std::string> getImmediateParentOf(
      int statementNumber, StmtType statementType) = 0;

  // return true if Parent(statementNumber, followingStatement) holds and false
  // otherwise
  virtual bool isParent(int statementNumber, int childStatement) = 0;

  // return all pairs (s1,s2) that satisfy Parent(s1, s2) and satisfying
  // statement type restriction
  virtual std::vector<std::pair<std::string, std::string>> getParentChildPairs(
      StmtType parentType, StmtType childType) = 0;

  // return all pairs (s1, s2) that satisfy Parent*(s1, s2) where s2 is of same
  // type as statementType and s1 is statementNumber
  virtual std::vector<std::string> getChildrenStarOf(
      int statementNumber, StmtType statementType) = 0;

  // return all pairs (s1, s2) that satisfy Parent*(s1, s2) where s1 is of same
  // type as statementType and s2 is statementNumber
  virtual std::vector<std::string> getParentStarOf(int statementNumber,
                                                   StmtType statementType) = 0;

  // return true if Parent*(statementNumber, followingStatement) holds and false
  // otherwise
  virtual bool isParentStar(int statementNumber, int childStatement) = 0;

  // return all pairs (s1,s2) that satisfy Parent*(s1, s2) and satisfying
  // statement type restriction
  virtual std::vector<std::pair<std::string, std::string>>
  getParentChildStarPairs(StmtType parentType, StmtType childType) = 0;
};