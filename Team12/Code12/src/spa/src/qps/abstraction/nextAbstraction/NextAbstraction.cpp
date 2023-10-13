#include "NextAbstraction.h"

/**
 * Next abstraction:
 * firstArg: Synonym OR Integer OR Wildcard
 * secondArg: Synonym OR Integer OR Wildcard
 */

// Next (StmtSynonym, StmtSynonym)
IntermediateTable NextAbstraction::evaluateSynonymSynonym() {
  if (this->firstArgValue == this->secondArgValue) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  return handleSynonymOrWildcardArgs();
}

// Next (StmtSynonym, StmtNumber)
IntermediateTable NextAbstraction::evaluateSynonymInteger() {
  return handleSecondArgInteger();
}

// Next (StmtSynonym, _)
IntermediateTable NextAbstraction::evaluateSynonymWildcard() {
  return handleSynonymOrWildcardArgs();
}

// Next (StmtNumber, StmtSynonym)
IntermediateTable NextAbstraction::evaluateIntegerSynonym() {
  return handleFirstArgInteger();
}

// Next (StmtNumber, StmtNumber)
IntermediateTable NextAbstraction::evaluateIntegerInteger() {
  return handleBothArgsInteger();
}

// Next (StmtNumber, _)
IntermediateTable NextAbstraction::evaluateIntegerWildcard() {
  return handleFirstArgInteger();
}

// Next (StmtNumber, StmtSynonym)
IntermediateTable NextAbstraction::evaluateWildcardSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Next (_, StmtNumber)
IntermediateTable NextAbstraction::evaluateWildcardInteger() {
  return handleSecondArgInteger();
}

// Next (_, _)
IntermediateTable NextAbstraction::evaluateWildcardWildcard() {
  return handleSynonymOrWildcardArgs();
}

/**
 * For handling cases where both args are non-integer
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
