#include "ParentReader.h"

std::vector<std::string> ParentReader::getImmediateChildrenOf(
    int stmt, StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = parentStore.getDirectSuccessorsOf(stmt, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
}

std::vector<std::string> ParentReader::getImmediateParentOf(int stmt,
                                                            StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = parentStore.getDirectAncestorsOf(stmt, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
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
      stmtStore.getStmtStmtFilterPredicates(stmtType1, stmtType2);

  auto rawRes = parentStore.getDirectRelations(stmtFilters);

  return CollectionUtils::transformIntIntToStrStrVector(rawRes);
}

// ================================== ParentT ==================================

std::vector<std::string> ParentReader::getChildrenStarOf(int stmt,
                                                         StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = parentStore.getSuccessorsTOf(stmt, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
}

std::vector<std::string> ParentReader::getParentStarOf(int stmt,
                                                       StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = parentStore.getAncestorsTOf(stmt, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
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
      stmtStore.getStmtStmtFilterPredicates(stmtType1, stmtType2);

  auto rawRes = parentStore.getRelationsT(stmtFilters);

  return CollectionUtils::transformIntIntToStrStrVector(rawRes);
}
