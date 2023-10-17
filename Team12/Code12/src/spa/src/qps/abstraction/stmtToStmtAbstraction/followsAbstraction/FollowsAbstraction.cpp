#include "FollowsAbstraction.h"

/**
 * Follows abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

IntermediateTable FollowsAbstraction::handleFirstArgInteger() {
  int firstStmtNumber = stoi(this->firstArgValue);
  StmtType secondStmtType = this->getSecondArgStmtType();
  string secondStmtSynonym = this->secondArgValue;

  string followingStmt = pkb.getFollowing(firstStmtNumber, secondStmtType);

  if (followingStmt != INVALID_STATEMENT_NUMBER) {
    return IntermediateTableFactory::buildIntermediateTable(secondStmtSynonym,
                                                            followingStmt);
  }

  return IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable FollowsAbstraction::handleSecondArgInteger() {
  StmtType firstStmtType = this->getFirstArgStmtType();
  string firstStmtSynonym = this->firstArgValue;
  int secondStmtNumber = stoi(this->secondArgValue);

  string followedStmt = pkb.getFollowed(secondStmtNumber, firstStmtType);
  if (followedStmt != INVALID_STATEMENT_NUMBER) {
    return IntermediateTableFactory::buildIntermediateTable(firstStmtSynonym,
                                                            followedStmt);
  }

  return IntermediateTableFactory::buildEmptyIntermediateTable();
}
