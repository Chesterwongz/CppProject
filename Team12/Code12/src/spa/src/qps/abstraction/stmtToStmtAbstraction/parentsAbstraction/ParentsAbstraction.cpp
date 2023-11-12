#include "ParentsAbstraction.h"

/**
 * Parents abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

bool ParentsAbstraction::isFirstSynonymInvalid() {
  bool isNotStmtOrWildcard =
      !(this->firstArg.isStmtSynonym() || this->firstArg.isWildcard());
  if (isNotStmtOrWildcard) {
    return true;
  }
  StmtType stmtType = this->getFirstArgStmtType();
  return stmtType != StmtType::STMT && stmtType != StmtType::IF &&
         stmtType != StmtType::WHILE;
}

bool ParentsAbstraction::hasPairs() { return this->pkb.hasParents(); }

vector<pair<string, string>> ParentsAbstraction::getAllPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return pkb.getParentChildPairs(firstStmtType, secondStmtType);
}

vector<string> ParentsAbstraction::getFirstStmt(int secondStmtNumber,
                                                StmtType firstStmtType) {
  return pkb.getImmediateParentOf(secondStmtNumber, firstStmtType);
}

vector<string> ParentsAbstraction::getSecondStmt(int firstStmtNumber,
                                                 StmtType secondStmtType) {
  return pkb.getImmediateChildrenOf(firstStmtNumber, secondStmtType);
}

bool ParentsAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isParent(stmtNum1, stmtNum2);
}
