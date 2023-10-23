#pragma once

#include <utility>
#include <vector>

#include "common/AliasTypes.h"

class INextStorage {
 public:
  virtual ~INextStorage() = default;
  virtual void addRelation(int from, int to) = 0;
  virtual IntSet getDirectSuccessors(int stmtNum) = 0;
  virtual IntSet getDirectAncestors(int stmtNum) = 0;
  virtual IntSet getSuccessorsT(int stmtNum) = 0;
  virtual IntSet getAncestorsT(int stmtNum) = 0;
  virtual bool hasDirectRelation(int firstStmtNum, int secondStmtNum) = 0;
  virtual bool hasRelationT(int firstStmtNum, int secondStmtNum) = 0;
  virtual std::vector<std::pair<int, int>> getAllDirectRelations() = 0;
  virtual void clearCache() = 0;
};
