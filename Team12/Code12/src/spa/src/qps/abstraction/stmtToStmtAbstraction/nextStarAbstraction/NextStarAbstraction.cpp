#include "NextStarAbstraction.h"

/**
 * Next Star abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

IntermediateTable NextStarAbstraction::handleSynonymOrWildcardArgs() {
  StmtType firstStmtType = this->getFirstArgStmtType();
  StmtType secondStmtType = this->getSecondArgStmtType();

  vector<pair<string, string>> nextStarPairs =
      pkb.getNextTPairs(firstStmtType, secondStmtType);

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      this->firstArgValue, this->secondArgValue, nextStarPairs);
}

IntermediateTable NextStarAbstraction::handleBothArgsInteger() {
  if (this->firstArgValue == this->secondArgValue) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  int firstStmtNumber = stoi(this->firstArgValue);
  int secondStmtNumber = stoi(this->secondArgValue);

  bool isNextT = pkb.isNextT(firstStmtNumber, secondStmtNumber);

  return isNextT ? IntermediateTableFactory::buildWildcardIntermediateTable()
                 : IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable NextStarAbstraction::handleFirstArgInteger() {
  int firstStmtNumber = stoi(this->firstArgValue);
  StmtType secondStmtType = this->getSecondArgStmtType();
  string secondStmtSynonym = this->secondArgValue;

  vector<string> nextStarSecondStmt =
      pkb.getNextTStmts(firstStmtNumber, secondStmtType);

  return IntermediateTableFactory::buildSingleColTable(secondStmtSynonym,
                                                       nextStarSecondStmt);
}

IntermediateTable NextStarAbstraction::handleSecondArgInteger() {
  StmtType firstStmtType = this->getFirstArgStmtType();
  string firstStmtSynonym = this->firstArgValue;
  int secondStmtNumber = stoi(this->secondArgValue);

  vector<string> nextStarFirstStmt =
      pkb.getPrevTStmts(secondStmtNumber, firstStmtType);

  return IntermediateTableFactory::buildSingleColTable(firstStmtSynonym,
                                                       nextStarFirstStmt);
}
