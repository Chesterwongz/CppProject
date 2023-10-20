#include "FollowsReader.h"

std::vector<std::string> FollowsReader::getFollowing(int stmt,
                                                     StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType) ||
      !followsStore.hasDirectSuccessors(stmt)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  const auto& rawRes = followsStore.getDirectSuccessors(stmt);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
}

std::vector<std::string> FollowsReader::getFollowed(int stmt,
                                                    StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType) ||
      !followsStore.hasDirectAncestors(stmt)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = followsStore.getDirectAncestors(stmt);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
}

bool FollowsReader::isFollows(int stmt1, int stmt2) {
  return followsStore.hasDirectRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>> FollowsReader::getFollowsPairs(
    StmtType stmtType1, StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType1) || !stmtStore.hasStmtType(stmtType2)) {
    return {};
  }

  auto stmtFilters =
      stmtStore.getStmtStmtFilterPredicates(stmtType1, stmtType2);

  auto rawRes = followsStore.getDirectRelations();

  return CollectionUtils::transformMapSetABToVectorUV(
      rawRes, CollectionUtils::getIntToStrMapperPair(), stmtFilters);
}

// ================================= FollowsT =================================

std::vector<std::string> FollowsReader::getFollowsStar(int stmt,
                                                       StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType) || !followsStore.hasSuccessorsT(stmt)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  const auto& rawRes = followsStore.getSuccessorsT(stmt);

  return CollectionUtils::transformIntSetToStrVector(rawRes, stmtFilter);
}

std::vector<std::string> FollowsReader::getFollowedStar(int stmt,
                                                        StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType) || !followsStore.hasAncestorsT(stmt)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  const auto& rawRes = followsStore.getAncestorsT(stmt);

  return CollectionUtils::transformIntSetToStrVector(rawRes, stmtFilter);
}

bool FollowsReader::isFollowsStar(int stmt1, int stmt2) {
  return followsStore.hasRelationT(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>>
FollowsReader::getFollowsStarPairs(StmtType stmtType1, StmtType stmtType2) {
  if (!stmtStore.hasStmtType(stmtType1) || !stmtStore.hasStmtType(stmtType2)) {
    return {};
  }

  auto stmtFilters =
      stmtStore.getStmtStmtFilterPredicates(stmtType1, stmtType2);

  const auto& rawRes = followsStore.getRelationsT();

  return CollectionUtils::transformMapSetABToVectorUV<int, int, std::string,
                                                      std::string>(
      rawRes, CollectionUtils::getIntToStrMapperPair(), stmtFilters);
}
