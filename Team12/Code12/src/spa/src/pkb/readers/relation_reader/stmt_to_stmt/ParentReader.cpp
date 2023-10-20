#include "ParentReader.h"

std::vector<std::string> ParentReader::getImmediateChildrenOf(
    int stmt, StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType) ||
      !parentStore.hasDirectSuccessors(stmt)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  const auto& rawRes = parentStore.getDirectSuccessors(stmt);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
}

std::vector<std::string> ParentReader::getImmediateParentOf(int stmt,
                                                            StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType) ||
      !parentStore.hasDirectAncestors(stmt)) {
    return {};
  }
  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  const auto& rawRes = parentStore.getDirectAncestors(stmt);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
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

  const auto& rawRes = parentStore.getDirectRelations();

  return CollectionUtils::transformMapSetABToVectorUV<int, int, std::string,
                                                      std::string>(
      rawRes, CollectionUtils::getIntToStrMapperPair(), stmtFilters);
}

// ================================== ParentT ==================================

std::vector<std::string> ParentReader::getChildrenStarOf(int stmt,
                                                         StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType) || !parentStore.hasSuccessorsT(stmt)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  const auto& rawRes = parentStore.getSuccessorsT(stmt);

  return CollectionUtils::transformIntSetToStrVector(rawRes, stmtFilter);
}

std::vector<std::string> ParentReader::getParentStarOf(int stmt,
                                                       StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType) || !parentStore.hasAncestorsT(stmt)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  const auto& rawRes = parentStore.getAncestorsT(stmt);

  return CollectionUtils::transformIntSetToStrVector(rawRes, stmtFilter);
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

  const auto& rawRes = parentStore.getRelationsT();

  return CollectionUtils::transformMapSetABToVectorUV<int, int, std::string,
                                                      std::string>(
      rawRes, CollectionUtils::getIntToStrMapperPair(), stmtFilters);
}
