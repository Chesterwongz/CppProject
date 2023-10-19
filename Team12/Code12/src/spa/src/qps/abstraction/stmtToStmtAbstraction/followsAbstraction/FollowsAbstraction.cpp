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

vector<string> FollowsAbstraction::getFirstStmt(int secondStmtNumber,
                                                StmtType firstStmtType) {
  return pkb.getFollowed(secondStmtNumber, firstStmtType);
}

vector<string> FollowsAbstraction::getSecondStmt(int firstStmtNumber,
                                                 StmtType secondStmtType) {
  return pkb.getFollowing(firstStmtNumber, secondStmtType);
}

bool FollowsAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isFollows(stmtNum1, stmtNum2);
}
