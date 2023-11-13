#include "NextStarAbstraction.h"

/**
 * Next Star abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */
bool NextStarAbstraction::isSelfReferencePossible() { return true; }

bool NextStarAbstraction::hasPairs() { return this->pkb.hasNextT(); }

vector<pair<string, string>> NextStarAbstraction::getAllPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return pkb.getNextTPairs(firstStmtType, secondStmtType);
}

vector<string> NextStarAbstraction::getFirstStmt(int s2, StmtType firstStmtType) {
  return pkb.getPrevTStmts(s2, firstStmtType);
}

vector<string> NextStarAbstraction::getSecondStmt(int s1, StmtType secondStmtType) {
  return pkb.getNextTStmts(s1, secondStmtType);
}

bool NextStarAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isNextT(stmtNum1, stmtNum2);
}
