#pragma once

#include <functional>
#include <string>
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

  [[nodiscard]] const std::unordered_set<int>& getAllStmtsOf(
      StmtType stmtType) const;

  [[nodiscard]] bool hasStmtType(StmtType stmtType) const;

  /**
   * Throws error if stmtType does not exist.
   * Must check if stmtType exists first with hasStmType.
   * @param stmtType
   * @return
   */
  [[nodiscard]] std::function<bool(int)> getStmtFilterPredicate(
      StmtType stmtType) const;

  [[nodiscard]] std::pair<std::function<bool(int)>, std::function<bool(int)>>
  getStmtStmtFilterPredicates(StmtType stmtType1, StmtType stmtType2) const;

  [[nodiscard]] std::pair<std::function<bool(int)>,
                          std::function<bool(std::string)>>
  getStmtStrFilterPredicates(StmtType stmtType1) const;
};
