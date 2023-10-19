#include "AffectsAbstraction.h"

/**
 * Affects abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

bool AffectsAbstraction::isSelfReferencePossible() { return true; }

vector<pair<string, string>> AffectsAbstraction::getAllPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return pkb.getAffectsPairs(firstStmtType, secondStmtType);
}

vector<string> AffectsAbstraction::getFirstStmt(int secondStmtNumber,
                                                StmtType firstStmtType) {
  return pkb.getAffects(secondStmtNumber, firstStmtType);
}

vector<string> AffectsAbstraction::getSecondStmt(int firstStmtNumber,
                                                 StmtType secondStmtType) {
  return pkb.getAffectedBy(firstStmtNumber, secondStmtType);
}

bool AffectsAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isAffects(stmtNum1, stmtNum2);
}
