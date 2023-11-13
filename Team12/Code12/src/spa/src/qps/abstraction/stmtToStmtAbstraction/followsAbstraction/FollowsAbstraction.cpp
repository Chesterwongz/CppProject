#include "FollowsAbstraction.h"

/**
 * Follows abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */
bool FollowsAbstraction::hasPairs() { return this->pkb.hasFollows(); }

vector<pair<string, string>> FollowsAbstraction::getAllPairs(StmtType type1,
                                                             StmtType type2) {
  return pkb.getFollowsPairs(type1, type2);
}

vector<string> FollowsAbstraction::getFirstStmt(int s2, StmtType type1) {
  return pkb.getFollowed(s2, type1);
}

vector<string> FollowsAbstraction::getSecondStmt(int s1, StmtType type2) {
  return pkb.getFollowing(s1, type2);
}

bool FollowsAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isFollows(stmtNum1, stmtNum2);
}
