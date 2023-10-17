#include "NextAbstraction.h"

/**
 * Next abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

IntermediateTable NextAbstraction::handleSynonymOrWildcardArgs() {
  StmtType firstStmtType = this->getFirstArgStmtType();
  StmtType secondStmtType = this->getSecondArgStmtType();

  vector<pair<string, string>> nextPairs =
      pkb.getNextPairs(firstStmtType, secondStmtType);

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      this->firstArgValue, this->secondArgValue, nextPairs);
}

IntermediateTable NextAbstraction::handleBothArgsInteger() {
  if (this->firstArgValue == this->secondArgValue) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  int firstStmtNumber = stoi(this->firstArgValue);
  int secondStmtNumber = stoi(this->secondArgValue);

  bool isNext = pkb.isNext(firstStmtNumber, secondStmtNumber);

  return isNext ? IntermediateTableFactory::buildWildcardIntermediateTable()
                : IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable NextAbstraction::handleFirstArgInteger() {
  int firstStmtNumber = stoi(this->firstArgValue);
  StmtType secondStmtType = this->getSecondArgStmtType();
  string secondStmtSynonym = this->secondArgValue;

  vector<string> nextSecondStmt =
      pkb.getNextStmts(firstStmtNumber, secondStmtType);

  return IntermediateTableFactory::buildSingleColTable(secondStmtSynonym,
                                                       nextSecondStmt);
}

IntermediateTable NextAbstraction::handleSecondArgInteger() {
  StmtType firstStmtType = this->getFirstArgStmtType();
  string firstStmtSynonym = this->firstArgValue;
  int secondStmtNumber = stoi(this->secondArgValue);

  vector<string> nextFirstStmt =
      pkb.getPrevStmts(secondStmtNumber, firstStmtType);

  return IntermediateTableFactory::buildSingleColTable(firstStmtSynonym,
                                                       nextFirstStmt);
}
