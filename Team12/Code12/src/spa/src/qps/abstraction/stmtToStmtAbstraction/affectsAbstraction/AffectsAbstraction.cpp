#include "AffectsAbstraction.h"

/**
 * Affects abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

bool AffectsAbstraction::isInvalidStmtType(StmtType stmtType) {
  return stmtType != StmtType::STMT && stmtType != StmtType::ASSIGN;
}

bool AffectsAbstraction::isFirstStmtTypeInvalid() {
  return isInvalidStmtType(this->getFirstArgStmtType());
}

bool AffectsAbstraction::isSecondStmtTypeInvalid() {
  return isInvalidStmtType(this->getSecondArgStmtType());
}

bool AffectsAbstraction::isSelfReferencePossible() { return true; }

vector<pair<string, string>> AffectsAbstraction::getAllPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  if (isInvalidStmtType(firstStmtType) || isInvalidStmtType(secondStmtType)) {
    return {};
  }
  return pkb.getAffectsPairs();
}

vector<string> AffectsAbstraction::getFirstStmt(int secondStmtNumber,
                                                StmtType firstStmtType) {
  if (isInvalidStmtType(firstStmtType)) {
    return {};
  }
  return pkb.getAffectedBy(secondStmtNumber, firstStmtType);
}

vector<string> AffectsAbstraction::getSecondStmt(int firstStmtNumber,
                                                 StmtType secondStmtType) {
  if (isInvalidStmtType(secondStmtType)) {
    return {};
  }
  return pkb.getAffects(firstStmtNumber, secondStmtType);
}

bool AffectsAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isAffects(stmtNum1, stmtNum2);
}
