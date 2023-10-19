#include "NextStarAbstraction.h"

/**
 * Next Star abstraction:
 * firstArg: Synonym OR Integer OR Wildcard
 * secondArg: Synonym OR Integer OR Wildcard
 */

// Next (StmtSynonym, StmtSynonym)
IntermediateTable NextStarAbstraction::evaluateSynonymSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Next (StmtSynonym, StmtNumber)
IntermediateTable NextStarAbstraction::evaluateSynonymInteger() {
  return handleSecondArgInteger();
}

// Next (StmtSynonym, _)
IntermediateTable NextStarAbstraction::evaluateSynonymWildcard() {
  return handleSynonymOrWildcardArgs();
}

// Next (StmtNumber, StmtSynonym)
IntermediateTable NextStarAbstraction::evaluateIntegerSynonym() {
  return handleFirstArgInteger();
}

// Next (StmtNumber, StmtNumber)
IntermediateTable NextStarAbstraction::evaluateIntegerInteger() {
  return handleBothArgsInteger();
}

// Next (StmtNumber, _)
IntermediateTable NextStarAbstraction::evaluateIntegerWildcard() {
  return handleFirstArgInteger();
}

// Next (StmtNumber, StmtSynonym)
IntermediateTable NextStarAbstraction::evaluateWildcardSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Next (_, StmtNumber)
IntermediateTable NextStarAbstraction::evaluateWildcardInteger() {
  return handleSecondArgInteger();
}

// Next (_, _)
IntermediateTable NextStarAbstraction::evaluateWildcardWildcard() {
  return handleSynonymOrWildcardArgs();
}

/**
 * For handling cases where both args are non-integer
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
