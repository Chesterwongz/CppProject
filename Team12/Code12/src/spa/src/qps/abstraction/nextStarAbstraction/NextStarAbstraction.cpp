#include "NextStarAbstraction.h"

/**
 * Next Star abstraction:
 * firstArg: Synonym OR Integer OR Wildcard
 * secondArg: Synonym OR Integer OR Wildcard
 */

// Next (StmtSynonym, StmtSynonym)
IntermediateTable NextStarAbstraction::evaluateSynonymSynonym() {
  if (this->firstArgValue == this->secondArgValue) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
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
      pkb.getNextStarPairs(firstStmtType, secondStmtType);

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

  bool isNextStar = pkb.isNextStar(firstStmtNumber, secondStmtNumber);

  return isNextStar ? IntermediateTableFactory::buildWildcardIntermediateTable()
                 : IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable NextStarAbstraction::handleFirstArgInteger() {
  int firstStmtNumber = stoi(this->firstArgValue);
  StmtType secondStmtType = this->getSecondArgStmtType();
  string secondStmtSynonym = this->secondArgValue;

  vector<string> nextStarSecondStmt =
      pkb.getNextStarSecondStmt(firstStmtNumber, secondStmtType);

  return IntermediateTableFactory::buildSingleColTable(secondStmtSynonym, nextStarSecondStmt);
}

IntermediateTable NextStarAbstraction::handleSecondArgInteger() {
  StmtType firstStmtType = this->getFirstArgStmtType();
  string firstStmtSynonym = this->firstArgValue;
  int secondStmtNumber = stoi(this->secondArgValue);

  vector<string> nextStarFirstStmt =
      pkb.getNextStarFirstStmt(secondStmtNumber, firstStmtType);

  return IntermediateTableFactory::buildSingleColTable(
      firstStmtSynonym, nextStarFirstStmt);
}
