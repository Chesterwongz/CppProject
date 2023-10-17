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

  vector<pair<string, string>> followStarPairs =
      pkb.getFollowsStar(firstStmtNumber, secondStmtType);

  // pass first col as wildcard so the table ignores integer column
  return IntermediateTableFactory::buildIntermediateTable(
      WILDCARD_KEYWORD, secondStmtSynonym, followStarPairs);
}

IntermediateTable FollowsStarAbstraction::handleSecondArgInteger() {
  StmtType firstStmtType = this->getFirstArgStmtType();
  string firstStmtSynonym = this->firstArgValue;
  int secondStmtNumber = stoi(this->secondArgValue);

  vector<pair<string, string>> followedStarPairs =
      pkb.getFollowedStar(secondStmtNumber, firstStmtType);

  // pass second col as wildcard so the table ignores integer column
  return IntermediateTableFactory::buildIntermediateTable(
      firstStmtSynonym, WILDCARD_KEYWORD, followedStarPairs);
}
