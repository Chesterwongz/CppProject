#include "FollowsStarAbstraction.h"

/**
 * Follows Star abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

bool FollowsStarAbstraction::hasPairs() { return this->pkb.hasFollowsT(); }

vector<pair<string, string>> FollowsStarAbstraction::getAllPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return pkb.getFollowsStarPairs(firstStmtType, secondStmtType);
}

vector<string> FollowsStarAbstraction::getFirstStmt(int secondStmtNumber,
                                                    StmtType firstStmtType) {
  return pkb.getFollowedStar(secondStmtNumber, firstStmtType);
}

vector<string> FollowsStarAbstraction::getSecondStmt(int firstStmtNumber,
                                                     StmtType secondStmtType) {
  return pkb.getFollowsStar(firstStmtNumber, secondStmtType);
}

bool FollowsStarAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isFollowsStar(stmtNum1, stmtNum2);
}
