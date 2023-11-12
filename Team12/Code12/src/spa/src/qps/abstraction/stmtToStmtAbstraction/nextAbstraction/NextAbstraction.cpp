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

vector<string> NextAbstraction::getFirstStmt(StmtType firstStmtType, int s2) {
  return pkb.getPrevStmts(firstStmtType, s2);
}

vector<string> NextAbstraction::getSecondStmt(StmtType secondStmtType, int s1) {
  return pkb.getNextStmts(secondStmtType, s1);
}

bool NextAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isNext(stmtNum1, stmtNum2);
}
