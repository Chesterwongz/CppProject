#include "StmtStore.h"

void StmtStore::addStmt(int stmt, StmtType stmtType) {
  stmtTypeToStmtMap[stmtType].insert(stmt);
  stmtTypeToStmtMap[StmtType::STMT].insert(stmt);
}
std::unordered_set<int> StmtStore::getStmtsForType(StmtType stmtType) const {
  if (stmtTypeToStmtMap.find(stmtType) == stmtTypeToStmtMap.end()) {
    return {};
  }
  return stmtTypeToStmtMap.at(stmtType);
}

bool StmtStore::hasStmtType(StmtType stmtType) const {
  return stmtTypeToStmtMap.count(stmtType);
}

std::function<bool(int)> StmtStore::getStmtFilterPredicate(
    StmtType stmtType) const {
  const auto& stmtSet = stmtTypeToStmtMap.at(stmtType);
  return PredicateUtils::isInSet<int>(stmtSet);
}

std::pair<std::function<bool(int)>, std::function<bool(int)>>
StmtStore::getStmtPairFilterPredicates(StmtType stmtType1,
                                       StmtType stmtType2) const {
  return std::make_pair(getStmtFilterPredicate(stmtType1),
                        getStmtFilterPredicate(stmtType2));
}
