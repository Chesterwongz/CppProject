#include "StmtToStmtReader.h"

std::vector<std::string> StmtToStmtReader::getDirectS2ByS1(int stmt1,
                                                           StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType2) || !store.hasDirectSuccessors(stmt1)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType2);

  const auto& rawRes = store.getDirectSuccessors(stmt1);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
}

std::vector<std::string> StmtToStmtReader::getDirectS1ByS2(int s2,
                                                           StmtType stmtType1) {
  if (!stmtStore.hasStmtType(stmtType1) || !store.hasDirectAncestors(s2)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType1);

  auto rawRes = store.getDirectAncestors(s2);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
}

bool StmtToStmtReader::hasDirectRelation(int stmt1, int stmt2) {
  return store.hasDirectRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>>
StmtToStmtReader::getDirectS1AndS2Pairs(StmtType stmtType1,
                                        StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType1) || !stmtStore.hasStmtType(stmtType2)) {
    return {};
  }

  auto stmtFilters =
      stmtStore.getStmtStmtFilterPredicates(stmtType1, stmtType2);

  auto rawRes = store.getDirectSuccessorMap();

  return CollectionUtils::intIntMapSetToStrPairVector(rawRes, stmtFilters);
}

bool StmtToStmtReader::hasDirectS1AndS2Pairs() {
  return !store.getDirectSuccessorMap().empty();
}

// ================================= FollowsT =================================

std::vector<std::string> StmtToStmtReader::getTransitiveS1ByS2(
    int s2, StmtType stmtType1) {
  if (!stmtStore.hasStmtType(stmtType1) || !store.hasAncestorsT(s2)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType1);

  const auto& rawRes = store.getAncestorsT(s2);

  return CollectionUtils::intSetToStrVector(rawRes, stmtFilter);
}

std::vector<std::string> StmtToStmtReader::getTransitiveS2ByS1(
    int s1, StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType2) || !store.hasSuccessorsT(s1)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType2);

  const auto& rawRes = store.getSuccessorsT(s1);

  return CollectionUtils::intSetToStrVector(rawRes, stmtFilter);
}

bool StmtToStmtReader::hasTransitiveRelation(int s1, int s2) {
  return store.hasRelationT(s1, s2);
}

std::vector<std::pair<std::string, std::string>>
StmtToStmtReader::getTransitiveS1AndS2Pairs(StmtType stmtType1,
                                            StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType1) || !stmtStore.hasStmtType(stmtType2)) {
    return {};
  }

  auto stmtFilters =
      stmtStore.getStmtStmtFilterPredicates(stmtType1, stmtType2);

  const auto& rawRes = store.getRelationsT();

  return CollectionUtils::intIntMapSetToStrPairVector(rawRes, stmtFilters);
}

bool StmtToStmtReader::hasTransitiveS1AndS2Pairs() {
  return !store.getRelationsT().empty();
}
