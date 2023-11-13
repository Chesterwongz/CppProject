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

vector<pair<string, string>> ParentsAbstraction::getAllPairs(StmtType type1,
                                                             StmtType type2) {
  return pkb.getParentChildPairs(type1, type2);
}

vector<string> ParentsAbstraction::getFirstStmt(int s2, StmtType type1) {
  return pkb.getImmediateParentOf(s2, type1);
}

vector<string> ParentsAbstraction::getSecondStmt(int s1, StmtType type2) {
  return pkb.getImmediateChildrenOf(s1, type2);
}

bool ParentsAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isParent(stmtNum1, stmtNum2);
}
