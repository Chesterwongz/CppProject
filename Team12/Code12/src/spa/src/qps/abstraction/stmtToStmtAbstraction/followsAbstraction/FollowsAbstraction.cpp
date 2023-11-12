#include "FollowsAbstraction.h"

/**
 * Follows abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

vector<pair<string, string>> FollowsAbstraction::getAllPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return pkb.getFollowsPairs(firstStmtType, secondStmtType);
}

vector<string> FollowsAbstraction::getFirstStmt(StmtType firstStmtType, int s2) {
  return pkb.getFollowed(firstStmtType, s2);
}

vector<string> FollowsAbstraction::getSecondStmt(StmtType secondStmtType, int s1) {
  return pkb.getFollowing(secondStmtType, s1);
}

bool FollowsAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isFollows(stmtNum1, stmtNum2);
}
