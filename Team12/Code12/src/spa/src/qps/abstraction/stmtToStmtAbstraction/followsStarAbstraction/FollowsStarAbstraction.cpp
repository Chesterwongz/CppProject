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

vector<string> FollowsStarAbstraction::getFirstStmt(int s2, StmtType firstStmtType) {
  return pkb.getFollowedStar(s2, firstStmtType);
}

vector<string> FollowsStarAbstraction::getSecondStmt(int s1, StmtType secondStmtType) {
  return pkb.getFollowsStar(s1, secondStmtType);
}

bool FollowsStarAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isFollowsStar(stmtNum1, stmtNum2);
}
