#include "StmtStore.h"

void StmtStore::addStmt(int stmt, StmtType stmtType) {
  stmtTypeToStmtMap[stmtType].insert(stmt);
}

bool StmtStore::hasStmtType(StmtType stmtType) const {
  return stmtType == StmtType::STMT ? !stmtTypeToStmtMap.empty()
                                    : stmtTypeToStmtMap.count(stmtType);
}

std::function<bool(int)> StmtStore::getStmtFilterPredicate(
    StmtType stmtType) const {
  if (stmtType == StmtType::STMT) {
    return PredicateUtils::truePredicate<int>();
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
                        PredicateUtils::truePredicate<std::string>());
}
