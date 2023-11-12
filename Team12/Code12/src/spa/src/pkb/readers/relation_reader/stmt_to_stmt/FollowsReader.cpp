#include "FollowsReader.h"

std::vector<std::string> FollowsReader::getFollowing(StmtType stmtType, int stmt = common::DEFAULT_STMT_NUM) {
  return reader.getDirectS2ByS1(stmtType, stmt);
}

std::vector<std::string> FollowsReader::getFollowed(StmtType stmtType, int stmt = common::DEFAULT_STMT_NUM) {
  return reader.getDirectS1ByS2(stmtType, stmt);
}

bool FollowsReader::isFollows(int stmt1, int stmt2) {
  return reader.hasDirectRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>> FollowsReader::getFollowsPairs(
    StmtType stmtType1, StmtType stmtType2) {
  return reader.getDirectS1AndS2Pairs(stmtType1, stmtType2);
}

// ================================= FollowsT =================================

std::vector<std::string> FollowsReader::getFollowsStar(StmtType stmtType, int stmt = common::DEFAULT_STMT_NUM) {
  return reader.getTransitiveS2ByS1(stmtType, stmt);
}

std::vector<std::string> FollowsReader::getFollowedStar(StmtType stmtType, int stmt = common::DEFAULT_STMT_NUM) {
  return reader.getTransitiveS1ByS2(stmtType, stmt);
}

bool FollowsReader::isFollowsStar(int stmt1, int stmt2) {
  return reader.hasTransitiveRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>>
FollowsReader::getFollowsStarPairs(StmtType stmtType1, StmtType stmtType2) {
  return reader.getTransitiveS1AndS2Pairs(stmtType1, stmtType2);
}
