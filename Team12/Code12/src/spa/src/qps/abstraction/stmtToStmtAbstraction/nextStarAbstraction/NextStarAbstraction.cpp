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

vector<string> NextStarAbstraction::getFirstStmt(int secondStmtNumber,
                                                 StmtType firstStmtType) {
  return pkb.getPrevTStmts(secondStmtNumber, firstStmtType);
}

vector<string> NextStarAbstraction::getSecondStmt(int firstStmtNumber,
                                                  StmtType secondStmtType) {
  return pkb.getNextTStmts(firstStmtNumber, secondStmtType);
}

bool NextStarAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isNextT(stmtNum1, stmtNum2);
}

// todo(yq): handle same synonym queries
