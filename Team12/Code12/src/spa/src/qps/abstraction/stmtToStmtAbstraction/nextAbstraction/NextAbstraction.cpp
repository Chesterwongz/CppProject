#include "NextAbstraction.h"

/**
 * Next abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

vector<pair<string, string>> NextAbstraction::getAllPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return pkb.getNextPairs(firstStmtType, secondStmtType);
}

bool NextAbstraction::hasPairs() { return this->pkb.hasNext(); }

vector<string> NextAbstraction::getFirstStmt(int s2, StmtType firstStmtType) {
  return pkb.getPrevStmts(s2, firstStmtType);
}

vector<string> NextAbstraction::getSecondStmt(int s1, StmtType secondStmtType) {
  return pkb.getNextStmts(s1, secondStmtType);
}

bool NextAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isNext(stmtNum1, stmtNum2);
}
