#include "ParentReader.h"

std::vector<std::string> ParentReader::getImmediateChildrenOf(
    int stmt, StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = parentStore.getDirectSuccessor(stmt, stmtFilter);

  return VectorUtils::transformIntToStrVector(rawRes);
}

std::vector<std::string> ParentReader::getImmediateParentOf(int stmt,
                                                            StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = parentStore.getDirectAncestor(stmt, stmtFilter);

  return VectorUtils::transformIntToStrVector(rawRes);
}

bool ParentReader::isParent(int stmt1, int stmt2) {
  return parentStore.hasDirectRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>>
ParentReader::getParentChildPairs(StmtType stmtType1, StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType1) || !stmtStore.hasStmtType(stmtType2)) {
    return {};
  }

  auto stmtFilters =
      stmtStore.getStmtPairFilterPredicates(stmtType1, stmtType2);

  auto rawRes = parentStore.getAllRelations(stmtFilters);

  return VectorUtils::transformIntIntToStrStrVector(rawRes);
}

// ================================== ParentT ==================================

std::vector<std::string> ParentReader::getChildrenStarOf(int stmt,
                                                         StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = parentStore.getSuccessorsOf(stmt, stmtFilter);

  return VectorUtils::transformIntToStrVector(rawRes);
}

std::vector<std::string> ParentReader::getParentStarOf(int stmt,
                                                       StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = parentStore.getAncestorsOf(stmt, stmtFilter);

  return VectorUtils::transformIntToStrVector(rawRes);
}

bool ParentReader::isParentStar(int stmt1, int stmt2) {
  return parentStore.hasRelationT(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>>
ParentReader::getParentChildStarPairs(StmtType stmtType1, StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType1) || !stmtStore.hasStmtType(stmtType2)) {
    return {};
  }

  auto stmtFilters =
      stmtStore.getStmtPairFilterPredicates(stmtType1, stmtType2);

  auto rawRes = parentStore.getAllRelationsT(stmtFilters);

  return VectorUtils::transformIntIntToStrStrVector(rawRes);
}
