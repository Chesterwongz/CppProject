#include "NextStarAbstraction.h"

/**
 * Next Star abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */
bool NextStarAbstraction::isSelfReferencePossible() { return true; }

vector<pair<string, string>> NextStarAbstraction::getAllPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return pkb.getNextTPairs(firstStmtType, secondStmtType);
}

vector<string> NextStarAbstraction::getFirstStmt(StmtType firstStmtType, int s2) {
  return pkb.getPrevTStmts(firstStmtType, s2);
}

vector<string> NextStarAbstraction::getSecondStmt(StmtType secondStmtType, int s1) {
  return pkb.getNextTStmts(secondStmtType, s1);
}

bool NextStarAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isNextT(stmtNum1, stmtNum2);
}
