#include "ParentsStarAbstraction.h"

/**
 * Parents star abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

IntermediateTable ParentsStarAbstraction::handleFirstArgInteger() {
  int firstArgStmtNumber = stoi(this->firstArgValue);
  StmtType secondArgStmtNumber = this->getSecondArgStmtType();
  string secondStmtSynonym = this->secondArgValue;

  vector<pair<string, string>> results =
      pkb.getChildrenStarOf(firstArgStmtNumber, secondArgStmtNumber);

  // pass first col as wildcard so the table ignores integer column
  return IntermediateTableFactory::buildIntermediateTable(
      WILDCARD_KEYWORD, secondStmtSynonym, results);
}

IntermediateTable ParentsStarAbstraction::handleSecondArgInteger() {
  string firstArgStmtSynonym = this->firstArgValue;
  StmtType firstArgStmtType = this->getFirstArgStmtType();
  int secondArgStmtNumber = stoi(this->secondArgValue);

  vector<pair<string, string>> results =
      pkb.getParentStarOf(secondArgStmtNumber, firstArgStmtType);

  // pass second col as wildcard so the table ignores the integer column
  return IntermediateTableFactory::buildIntermediateTable(
      firstArgStmtSynonym, WILDCARD_KEYWORD, results);
}
