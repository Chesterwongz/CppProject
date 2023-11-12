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

vector<pair<string, string>> ParentsStarAbstraction::getAllPairs(
    StmtType firstStmtType, StmtType secondStmtType) {
  return pkb.getParentChildStarPairs(firstStmtType, secondStmtType);
}

vector<string> ParentsStarAbstraction::getFirstStmt(StmtType firstStmtType,
                                                    int s2) {
  return pkb.getParentStarOf(firstStmtType, s2);
}

vector<string> ParentsStarAbstraction::getSecondStmt(StmtType secondStmtType,
                                                     int s1) {
  return pkb.getChildrenStarOf(secondStmtType, s1);
}

bool ParentsStarAbstraction::isStmtRelatedToStmt(int stmtNum1, int stmtNum2) {
  return pkb.isParentStar(stmtNum1, stmtNum2);
}
