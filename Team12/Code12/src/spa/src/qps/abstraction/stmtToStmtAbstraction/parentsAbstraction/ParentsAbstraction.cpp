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

  vector<pair<string, string>> results =
      pkb.getImmediateChildrenOf(firstArgStmtNumber, secondStmtType);

  // pass first col as wildcard so the table ignores integer column
  return IntermediateTableFactory::buildIntermediateTable(
      WILDCARD_KEYWORD, secondStmtSynonym, results);
}

IntermediateTable ParentsAbstraction::handleSecondArgInteger() {
  string firstArgStmtSynonym = this->firstArgValue;
  StmtType firstArgStmtType = this->getFirstArgStmtType();
  int secondArgStmtNumber = stoi(this->secondArgValue);
  vector<pair<string, string>> results;

  pair<string, string> immediateParent =
      pkb.getImmediateParentOf(secondArgStmtNumber, firstArgStmtType);
  if (immediateParent.first.empty() && immediateParent.second.empty()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  return IntermediateTableFactory::buildIntermediateTable(
      firstArgStmtSynonym, immediateParent.first);
}
