#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "common/Constants.h"
#include "common/StmtTypes.h"
#include "pkb/utils/PredicateUtils.h"

class StmtStore {
 private:
  std::unordered_map<StmtType, std::unordered_set<int>> stmtTypeToStmtMap;

 public:
  void addStmt(int stmt, StmtType stmtType);

  [[nodiscard]] bool hasStmtType(StmtType stmtType) const;

  // returns -1 if stmt doesnt exist, or stmt if it does
  [[nodiscard]] int getStmt(int stmt, StmtType stmtType) const;

  [[nodiscard]] const std::unordered_set<int>& getStmts(
      StmtType stmtType) const;

  [[nodiscard]] std::function<bool(int)> getStmtFilterPredicate(
      StmtType stmtType) const;

  [[nodiscard]] std::pair<std::function<bool(int)>, std::function<bool(int)>>
  getStmtPairFilterPredicates(StmtType stmtType1, StmtType stmtType2) const;
};
