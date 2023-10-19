#include "FollowsReader.h"

std::vector<std::string> FollowsReader::getFollowing(int stmt,
                                                     StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = followsStore.getDirectSuccessorsOf(stmt, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
}

std::vector<std::string> FollowsReader::getFollowed(int stmt,
                                                    StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = followsStore.getDirectAncestorsOf(stmt, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
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

  auto rawRes = followsStore.getDirectRelations(stmtFilters);

  return CollectionUtils::transformIntIntToStrStrVector(rawRes);
}

// ================================= FollowsT =================================

std::vector<std::string> FollowsReader::getFollowsStar(int stmt,
                                                       StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = followsStore.getSuccessorsTOf(stmt, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
}

std::vector<std::string> FollowsReader::getFollowedStar(int stmt,
                                                        StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  auto rawRes = followsStore.getAncestorsTOf(stmt, stmtFilter);

  return CollectionUtils::transformIntToStrVector(rawRes);
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

  auto rawRes = followsStore.getRelationsT(stmtFilters);

  return CollectionUtils::transformIntIntToStrStrVector(rawRes);
}
