#include "FollowsStarAbstraction.h"

/**
 * Follows Star abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */
IntermediateTable FollowsStarAbstraction::handleSynonymOrWildcardArgs() {
  StmtType firstStmtType = this->getFirstArgStmtType();
  StmtType secondStmtType = this->getSecondArgStmtType();

  vector<pair<string, string>> followPairs =
      pkb.getFollowsStarPairs(firstStmtType, secondStmtType);

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      this->firstArgValue, this->secondArgValue, followPairs);
}

IntermediateTable FollowsStarAbstraction::handleBothArgsInteger() {
  if (this->firstArgValue == this->secondArgValue) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  int firstStmtNumber = stoi(this->firstArgValue);
  int secondStmtNumber = stoi(this->secondArgValue);

  bool isValid = pkb.isFollowsStar(firstStmtNumber, secondStmtNumber);

  return isValid ? IntermediateTableFactory::buildWildcardIntermediateTable()
                 : IntermediateTableFactory::buildEmptyIntermediateTable();
}

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
