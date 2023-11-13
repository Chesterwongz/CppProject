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

vector<string> NextAbstraction::getFirstStmt(int secondStmtNumber,
                                             StmtType firstStmtType) {
  return pkb.getPrevStmts(secondStmtNumber, firstStmtType);
}

vector<string> NextAbstraction::getSecondStmt(int firstStmtNumber,
                                              StmtType secondStmtType) {
  return pkb.getNextStmts(firstStmtNumber, secondStmtType);
}

bool NextAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isNext(stmtNum1, stmtNum2);
}
