#include "ParentsStarAbstraction.h"

/**
 * Parents star abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

IntermediateTable ParentsStarAbstraction::handleFirstArgInteger() {
  int firstArgStmtNumber = stoi(this->firstArgValue);
  StmtType secondArgStmtType = this->getSecondArgStmtType();
  string secondStmtSynonym = this->secondArgValue;

  vector<string> results =
      pkb.getChildrenStarOf(firstArgStmtNumber, secondArgStmtType);

  return IntermediateTableFactory::buildSingleColTable(secondStmtSynonym,
                                                       results);
}

IntermediateTable ParentsStarAbstraction::handleSecondArgInteger() {
  string firstArgStmtSynonym = this->firstArgValue;
  StmtType firstArgStmtType = this->getFirstArgStmtType();
  int secondArgStmtNumber = stoi(this->secondArgValue);

  vector<string> results =
      pkb.getParentStarOf(secondArgStmtNumber, firstArgStmtType);

  return IntermediateTableFactory::buildSingleColTable(firstArgStmtSynonym,
                                                       results);
}
