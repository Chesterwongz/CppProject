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

  [[nodiscard]] std::unordered_set<int> getStmtsForType(StmtType stmtType) const;

  [[nodiscard]] bool hasStmtType(StmtType stmtType) const;

  [[nodiscard]] std::function<bool(int)> getStmtFilterPredicate(
      StmtType stmtType) const;

  [[nodiscard]] std::pair<std::function<bool(int)>, std::function<bool(int)>>
  getStmtPairFilterPredicates(StmtType stmtType1, StmtType stmtType2) const;
};
