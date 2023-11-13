#include "FollowsStarAbstraction.h"

/**
 * Follows Star abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

bool FollowsStarAbstraction::hasPairs() { return this->pkb.hasFollowsT(); }

vector<pair<string, string>> FollowsStarAbstraction::getAllPairs(
    StmtType type1, StmtType type2) {
  return pkb.getFollowsStarPairs(type1, type2);
}

vector<string> FollowsStarAbstraction::getFirstStmt(int s2, StmtType type1) {
  return pkb.getFollowedStar(s2, type1);
}

vector<string> FollowsStarAbstraction::getSecondStmt(int s1, StmtType type2) {
  return pkb.getFollowsStar(s1, type2);
}

bool FollowsStarAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isFollowsStar(stmtNum1, stmtNum2);
}
