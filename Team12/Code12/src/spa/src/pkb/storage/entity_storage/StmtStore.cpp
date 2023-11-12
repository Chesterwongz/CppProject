#include "StmtStore.h"

void StmtStore::addStmt(int stmt, StmtType stmtType) {
  stmtTypeToStmtMap[stmtType].insert(stmt);
  stmtTypeToStmtMap[StmtType::STMT].insert(stmt);
}

bool StmtStore::hasStmt(int stmt, StmtType stmtType) const {
  return stmtTypeToStmtMap.count(stmtType) &&
         stmtTypeToStmtMap.at(stmtType).count(stmt);
}

bool StmtStore::hasStmtType(StmtType stmtType) const {
  return stmtTypeToStmtMap.count(stmtType);
}

const std::unordered_set<int>& StmtStore::getAllStmtsOf(
    StmtType stmtType) const {
  return stmtTypeToStmtMap.at(stmtType);
}

std::function<bool(int)> StmtStore::getStmtFilterPredicate(
    StmtType stmtType) const {
  if (stmtType == StmtType::STMT) {  // Optimization.
    return PredicateUtils::returnTrue<int>();
  }
  const auto& stmtSet = stmtTypeToStmtMap.at(stmtType);
  return PredicateUtils::isInSet<int>(stmtSet);
}

std::pair<std::function<bool(int)>, std::function<bool(int)>>
StmtStore::getStmtStmtFilterPredicates(StmtType stmtType1,
                                       StmtType stmtType2) const {
  return std::make_pair(getStmtFilterPredicate(stmtType1),
                        getStmtFilterPredicate(stmtType2));
}

std::pair<std::function<bool(int)>, std::function<bool(std::string)>>
StmtStore::getStmtStrFilterPredicates(StmtType stmtType1) const {
  return std::make_pair(getStmtFilterPredicate(stmtType1),
                        PredicateUtils::returnTrue<std::string>());
}
