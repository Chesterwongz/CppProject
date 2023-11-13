#include "FollowsReader.h"

std::vector<std::string> FollowsReader::getFollowing(int stmt, StmtType stmtType) {
  return reader.getDirectS2ByS1(stmt, stmtType);
}

std::vector<std::string> FollowsReader::getFollowed(int stmt, StmtType stmtType) {
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
  return reader.hasDirectS1AndS2Pairs();
}

// ================================= FollowsT =================================

std::vector<std::string> FollowsReader::getFollowsStar(int s1, StmtType type2) {
  return reader.getTransitiveS2ByS1(s1, type2);
}

std::vector<std::string> FollowsReader::getFollowedStar(int s2, StmtType type1) {
  return reader.getTransitiveS1ByS2(s2, type1);
}

bool FollowsReader::isFollowsStar(int stmt1, int stmt2) {
  return reader.hasTransitiveRelation(stmt1, stmt2);
}

std::vector<std::pair<std::string, std::string>>
FollowsReader::getFollowsStarPairs(StmtType stmtType1, StmtType stmtType2) {
  return reader.getTransitiveS1AndS2Pairs(stmtType1, stmtType2);
}

bool FollowsReader::hasFollowsT() {
  return reader.hasTransitiveS1AndS2Pairs();
}
