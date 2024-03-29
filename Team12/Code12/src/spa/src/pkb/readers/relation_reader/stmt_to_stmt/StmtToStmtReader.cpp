#include "StmtToStmtReader.h"

std::vector<std::string> StmtToStmtReader::getDirectS2ByS1(int s1,
                                                           StmtType type2) {
  if (!stmtStore.hasStmtType(type2) ||
      (s1 != common::WILDCARD_STMT_NUM && !store.hasDirectSuccessors(s1))) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(type2);
  std::unordered_set<int> rawRes;
  if (s1 == common::WILDCARD_STMT_NUM) {
    rawRes = store.getDirectSuccessors();
  } else {
    rawRes = store.getDirectSuccessors(s1);
  }
  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
}

std::vector<std::string> StmtToStmtReader::getDirectS1ByS2(int s2,
                                                           StmtType type1) {
  if (!stmtStore.hasStmtType(type1) ||
      (s2 != common::WILDCARD_STMT_NUM && !store.hasDirectAncestors(s2))) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(type1);
  std::unordered_set<int> rawRes;
  if (s2 == common::WILDCARD_STMT_NUM) {
    rawRes = store.getDirectAncestors();
  } else {
    rawRes = store.getDirectAncestors(s2);
  }
  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
}

bool StmtToStmtReader::hasDirectRelation(int s1, int s2) {
  if (s1 == common::WILDCARD_STMT_NUM) {
    return store.hasDirectAncestors(s2);
  } else if (s2 == common::WILDCARD_STMT_NUM) {
    return store.hasDirectSuccessors(s1);
  } else {
    return store.hasDirectRelation(s1, s2);
  }
}

std::vector<std::pair<std::string, std::string>>
StmtToStmtReader::getDirectS1AndS2Pairs(StmtType type1, StmtType type2) {
  if (!stmtStore.hasStmtType(type1) || !stmtStore.hasStmtType(type2)) {
    return {};
  }

  auto stmtFilters = stmtStore.getStmtStmtFilterPredicates(type1, type2);

  auto rawRes = store.getDirectSuccessorMap();

  return CollectionUtils::intIntMapSetToStrPairVector(rawRes, stmtFilters);
}

bool StmtToStmtReader::hasDirectS1AndS2Pairs() {
  return !store.getDirectSuccessorMap().empty();
}

// ================================= FollowsT =================================

std::vector<std::string> StmtToStmtReader::getTransitiveS1ByS2(int s2,
                                                               StmtType type1) {
  if (!stmtStore.hasStmtType(type1) ||
      (s2 != common::WILDCARD_STMT_NUM && !store.hasAncestorsT(s2))) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(type1);
  std::unordered_set<int> rawRes;
  if (s2 == common::WILDCARD_STMT_NUM) {
    rawRes = store.getDirectAncestors();
  } else {
    rawRes = store.getAncestorsT(s2);
  }
  return CollectionUtils::intSetToStrVector(rawRes, stmtFilter);
}

std::vector<std::string> StmtToStmtReader::getTransitiveS2ByS1(int s1,
                                                               StmtType type2) {
  if (!stmtStore.hasStmtType(type2) ||
      (s1 != common::WILDCARD_STMT_NUM && !store.hasSuccessorsT(s1))) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(type2);
  std::unordered_set<int> rawRes;
  if (s1 == common::WILDCARD_STMT_NUM) {
    rawRes = store.getDirectSuccessors();
  } else {
    rawRes = store.getSuccessorsT(s1);
  }
  return CollectionUtils::intSetToStrVector(rawRes, stmtFilter);
}

bool StmtToStmtReader::hasTransitiveRelation(int s1, int s2) {
  if (s1 == common::WILDCARD_STMT_NUM) {
    return store.hasAncestorsT(s2);
  } else if (s2 == common::WILDCARD_STMT_NUM) {
    return store.hasSuccessorsT(s1);
  } else {
    return store.hasRelationT(s1, s2);
  }
}

std::vector<std::pair<std::string, std::string>>
StmtToStmtReader::getTransitiveS1AndS2Pairs(StmtType type1, StmtType type2) {
  if (!stmtStore.hasStmtType(type1) || !stmtStore.hasStmtType(type2)) {
    return {};
  }

  auto stmtFilters = stmtStore.getStmtStmtFilterPredicates(type1, type2);

  const auto& rawRes = store.getRelationsT();

  return CollectionUtils::intIntMapSetToStrPairVector(rawRes, stmtFilters);
}

bool StmtToStmtReader::hasTransitiveS1AndS2Pairs() {
  return !store.getRelationsT().empty();
}
