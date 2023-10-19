#include "NextStarAbstraction.h"

/**
 * Next Star abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

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
IntermediateTable NextStarAbstraction::evaluateSynonymSynonym() {
  return handleSynonymOrWildcardArgs();
}

IntermediateTable NextStarAbstraction::evaluateIntegerInteger() {
  return handleBothArgsInteger();
}
// todo(yq): handle same synonym queries
