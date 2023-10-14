#include "FollowsReader.h"

// TODO(Chester): Follow the FollowsStar implementation
std::string FollowsReader::getFollowing(int stmt, StmtType stmtType) {
  if (!followsStore.hasDirectSuccessor(stmt)) {
    return common::INVALID_STMT_STR;
  }
  const auto& followingStmtSet = followsStore.getDirectSuccessor(stmt);
  assert(followingStmtSet.size() == 1);
  int followingStmt = *(followingStmtSet.begin());
  return std::to_string(stmtStore.getStmt(followingStmt, stmtType));
}

std::string FollowsReader::getFollowed(int stmt, StmtType stmtType) {
  if (!followsStore.hasDirectAncestor(stmt)) {
    return common::INVALID_STMT_STR;
  }
  const auto& followedStmtSet = followsStore.getDirectAncestor(stmt);
  assert(followedStmtSet.size() == 1);
  int followedStmt = *(followedStmtSet.begin());
  return std::to_string(stmtStore.getStmt(followedStmt, stmtType));
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
      stmtStore.getStmtPairFilterPredicates(stmtType1, stmtType2);

  std::vector<std::pair<int, int>> rawRes =
      followsStore.getAllRelations(stmtFilters.first, stmtFilters.second);
  return VectorUtils::transformIntIntToStrStrVector(rawRes);
}

// ================================= FollowsT =================================

std::vector<std::string> FollowsReader::getFollowsStar(int stmt,
                                                       StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  std::vector<int> rawRes = followsStore.getSuccessorsOf(stmt, stmtFilter);

  return VectorUtils::transformIntToStrVector(rawRes);
}

std::vector<std::string> FollowsReader::getFollowedStar(int stmt,
                                                        StmtType stmtType) {
  if (!stmtStore.hasStmtType(stmtType)) {
    return {};
  }

  auto stmtFilter = stmtStore.getStmtFilterPredicate(stmtType);

  std::vector<int> rawRes = followsStore.getAncestorsOf(stmt, stmtFilter);

  return VectorUtils::transformIntToStrVector(rawRes);
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
      stmtStore.getStmtPairFilterPredicates(stmtType1, stmtType2);

  std::vector<std::pair<int, int>> rawRes =
      followsStore.getAllRelationsT(stmtFilters.first, stmtFilters.second);
  return VectorUtils::transformIntIntToStrStrVector(rawRes);
}
