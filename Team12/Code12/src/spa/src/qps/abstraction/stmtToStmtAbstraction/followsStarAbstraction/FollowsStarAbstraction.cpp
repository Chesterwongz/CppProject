#include "FollowsStarAbstraction.h"

/**
 * Follows Star abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

IntermediateTable FollowsStarAbstraction::handleFirstArgInteger() {
  int firstStmtNumber = stoi(this->firstArgValue);
  StmtType secondStmtType = this->getSecondArgStmtType();
  string secondStmtSynonym = this->secondArgValue;

  vector<string> followsStars =
      pkb.getFollowsStar(firstStmtNumber, secondStmtType);

  return IntermediateTableFactory::buildSingleColTable(secondStmtSynonym,
                                                       followsStars);
}

IntermediateTable FollowsStarAbstraction::handleSecondArgInteger() {
  StmtType firstStmtType = this->getFirstArgStmtType();
  string firstStmtSynonym = this->firstArgValue;
  int secondStmtNumber = stoi(this->secondArgValue);

  vector<string> followedStars =
      pkb.getFollowedStar(secondStmtNumber, firstStmtType);

  return IntermediateTableFactory::buildSingleColTable(firstStmtSynonym,
                                                       followedStars);
}
