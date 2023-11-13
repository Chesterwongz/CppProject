#include "ParentsStarAbstraction.h"

/**
 * Parents star abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

bool ParentsStarAbstraction::isFirstSynonymInvalid() {
  bool isNotStmtOrWildcard =
      !(this->firstArg.isStmtSynonym() || this->firstArg.isWildcard());
  if (isNotStmtOrWildcard) {
    return true;
  }
  StmtType stmtType = this->getFirstArgStmtType();
  return stmtType != StmtType::STMT && stmtType != StmtType::IF &&
         stmtType != StmtType::WHILE;
}

bool ParentsStarAbstraction::hasPairs() { return this->pkb.hasParentsT(); }

vector<pair<string, string>> ParentsStarAbstraction::getAllPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return pkb.getParentChildStarPairs(firstStmtType, secondStmtType);
}

vector<string> ParentsStarAbstraction::getFirstStmt(int s2, StmtType firstStmtType) {
  return pkb.getParentStarOf(s2, firstStmtType);
}

vector<string> ParentsStarAbstraction::getSecondStmt(int s1, StmtType secondStmtType) {
  return pkb.getChildrenStarOf(s1, secondStmtType);
}

bool ParentsStarAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isParentStar(stmtNum1, stmtNum2);
}
