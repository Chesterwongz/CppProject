#include "FollowsStarAbstraction.h"

/**
 * Follows Star abstraction:
 * firstArg: Synonym OR Integer OR Wildcard
 * secondArg: Synonym OR Integer OR Wildcard
 */

// Follows (StmtSynonym, StmtSynonym)
IntermediateTable FollowsStarAbstraction::evaluateSynonymSynonym() {
  if (this->firstArgValue == this->secondArgValue) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  return handleSynonymOrWildcardArgs();
}

// Follows (StmtSynonym, StmtNumber)
IntermediateTable FollowsStarAbstraction::evaluateSynonymInteger() {
  return handleSecondArgInteger();
}

// Follows (StmtSynonym, _)
IntermediateTable FollowsStarAbstraction::evaluateSynonymWildcard() {
  return handleSynonymOrWildcardArgs();
}

// Follows (StmtNumber, StmtSynonym)
IntermediateTable FollowsStarAbstraction::evaluateIntegerSynonym() {
  return handleFirstArgInteger();
}

// Follows (StmtNumber, StmtNumber)
IntermediateTable FollowsStarAbstraction::evaluateIntegerInteger() {
  return handleBothArgsInteger();
}

// Follows (StmtNumber, _)
IntermediateTable FollowsStarAbstraction::evaluateIntegerWildcard() {
  return handleFirstArgInteger();
}

// Follows (StmtNumber, StmtSynonym)
IntermediateTable FollowsStarAbstraction::evaluateWildcardSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Follows (_, StmtNumber)
IntermediateTable FollowsStarAbstraction::evaluateWildcardInteger() {
  return handleSecondArgInteger();
}

// Follows (_, _)
IntermediateTable FollowsStarAbstraction::evaluateWildcardWildcard() {
  return handleSynonymOrWildcardArgs();
}

/**
 * For handling cases where both args are non-integer
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

  vector<string> followsStars =
      pkb.getFollowsStar(firstStmtNumber, secondStmtType);

  // pass first col as wildcard so the table ignores integer column
  return IntermediateTableFactory::buildSingleColTable(secondStmtSynonym,
                                                       followsStars);
}

IntermediateTable FollowsStarAbstraction::handleSecondArgInteger() {
  StmtType firstStmtType = this->getFirstArgStmtType();
  string firstStmtSynonym = this->firstArgValue;
  int secondStmtNumber = stoi(this->secondArgValue);

  vector<string> followedStars =
      pkb.getFollowedStar(secondStmtNumber, firstStmtType);

  // pass second col as wildcard so the table ignores integer column
  return IntermediateTableFactory::buildSingleColTable(firstStmtSynonym,
                                                       followedStars);
}
