#include "StmtStore.h"

void StmtStore::addStmt(int stmt, StmtType stmtType) {
  stmtTypeToStmtMap[stmtType].insert(stmt);
}

bool StmtStore::hasStmtType(StmtType stmtType) const {
  return stmtTypeToStmtMap.count(stmtType);
}

int StmtStore::getStmt(int stmt, StmtType stmtType) const {
  const auto& it = stmtTypeToStmtMap.find(stmtType);
  if (it == stmtTypeToStmtMap.end() || !it->second.count(stmt)) {
    return common::INVALID_STMT_NUM;
  }
  return stmt;
}

const std::unordered_set<int>& StmtStore::getStmts(StmtType stmtType) const {
  return stmtTypeToStmtMap.at(stmtType);
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
