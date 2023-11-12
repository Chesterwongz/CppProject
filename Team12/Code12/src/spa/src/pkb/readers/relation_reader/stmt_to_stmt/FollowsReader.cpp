#include "FollowsReader.h"

std::vector<std::string> FollowsReader::getFollowing(int stmt,
                                                     StmtType stmtType) {
  return reader.getDirectS2ByS1(stmt, stmtType);
}

std::vector<std::string> FollowsReader::getFollowed(int stmt,
                                                    StmtType stmtType) {
  return reader.getDirectS1ByS2(stmt, stmtType);
}

bool FollowsReader::isFollows(int stmt1, int stmt2) {
  return reader.hasDirectRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>> FollowsReader::getFollowsPairs(
    StmtType stmtType1, StmtType stmtType2) {
  return reader.getDirectS1AndS2Pairs(stmtType1, stmtType2);
}

bool FollowsReader::hasFollows() {
  return stmtStore.hasStmt() && !followsStore.getDirectRelations().empty();
}

// ================================= FollowsT =================================

std::vector<std::string> FollowsReader::getFollowsStar(int stmt,
                                                       StmtType stmtType) {
  return reader.getTransitiveS2ByS1(stmt, stmtType);
}

std::vector<std::string> FollowsReader::getFollowedStar(int stmt,
                                                        StmtType stmtType) {
  return reader.getTransitiveS1ByS2(stmt, stmtType);
}

bool FollowsReader::isFollowsStar(int stmt1, int stmt2) {
  return reader.hasTransitiveRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>>
FollowsReader::getFollowsStarPairs(StmtType stmtType1, StmtType stmtType2) {
  return reader.getTransitiveS1AndS2Pairs(stmtType1, stmtType2);
}

bool FollowsReader::hasFollowsT() {
  return stmtStore.hasStmt() && !followsStore.getRelationsT().empty();
}
