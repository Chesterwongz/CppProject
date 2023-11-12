#include "FollowsStarAbstraction.h"

/**
 * Follows Star abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

vector<pair<string, string>> FollowsStarAbstraction::getAllPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return pkb.getFollowsStarPairs(firstStmtType, secondStmtType);
}

vector<string> FollowsStarAbstraction::getFirstStmt(StmtType firstStmtType, int s2) {
  return pkb.getFollowedStar(firstStmtType, s2);
}

vector<string> FollowsStarAbstraction::getSecondStmt(StmtType secondStmtType, int s1) {
  return pkb.getFollowsStar(secondStmtType, s1);
}

bool FollowsStarAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isFollowsStar(stmtNum1, stmtNum2);
}
