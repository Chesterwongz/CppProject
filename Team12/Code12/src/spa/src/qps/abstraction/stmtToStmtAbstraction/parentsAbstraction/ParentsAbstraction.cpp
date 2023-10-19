#include "ParentsAbstraction.h"

/**
 * Parents abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

IntermediateTable ParentsAbstraction::handleFirstArgInteger() {
  int firstArgStmtNumber = stoi(this->firstArgValue);
  StmtType secondStmtType = this->getSecondArgStmtType();
  string secondStmtSynonym = this->secondArgValue;

  vector<string> results =
      pkb.getImmediateChildrenOf(firstArgStmtNumber, secondStmtType);

  return IntermediateTableFactory::buildSingleColTable(secondStmtSynonym,
                                                       results);
}

IntermediateTable ParentsAbstraction::handleSecondArgInteger() {
  string firstArgStmtSynonym = this->firstArgValue;
  StmtType firstArgStmtType = this->getFirstArgStmtType();
  int secondArgStmtNumber = stoi(this->secondArgValue);
  vector<pair<string, string>> results;

  vector<string> immediateParent =
      pkb.getImmediateParentOf(secondArgStmtNumber, firstArgStmtType);

  return IntermediateTableFactory::buildSingleColTable(firstArgStmtSynonym,
                                                       immediateParent);
}
