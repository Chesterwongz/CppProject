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

  vector<string> followingStmt =
      pkb.getFollowing(firstStmtNumber, secondStmtType);

  return IntermediateTableFactory::buildSingleColTable(secondStmtSynonym,
                                                       followingStmt);
}

IntermediateTable FollowsAbstraction::handleSecondArgInteger() {
  StmtType firstStmtType = this->getFirstArgStmtType();
  string firstStmtSynonym = this->firstArgValue;
  int secondStmtNumber = stoi(this->secondArgValue);

  vector<string> followedStmt =
      pkb.getFollowed(secondStmtNumber, firstStmtType);

  return IntermediateTableFactory::buildSingleColTable(firstStmtSynonym,
                                                       followedStmt);
}
