#include "NextStarAbstraction.h"

/**
 * Next Star abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */
bool NextStarAbstraction::isSelfReferencePossible() { return true; }

bool NextStarAbstraction::hasPairs() { return this->pkb.hasNextT(); }

vector<pair<string, string>> NextStarAbstraction::getAllPairs(StmtType type1,
                                                              StmtType type2) {
  return pkb.getNextTPairs(type1, type2);
}

vector<string> NextStarAbstraction::getFirstStmt(int s2, StmtType type1) {
  return pkb.getPrevTStmts(s2, type1);
}

vector<string> NextStarAbstraction::getSecondStmt(int s1, StmtType type2) {
  return pkb.getNextTStmts(s1, type2);
}

bool NextStarAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isNextT(stmtNum1, stmtNum2);
}
