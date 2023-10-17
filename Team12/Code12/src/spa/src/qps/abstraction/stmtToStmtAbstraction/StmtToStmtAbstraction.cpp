#include "StmtToStmtAbstraction.h"

/**
 * StmtToStmtAbstraction abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

// Abstraction (StmtSynonym, StmtSynonym)
IntermediateTable StmtToStmtAbstraction ::evaluateSynonymSynonym() {
  if (this->firstArgValue == this->secondArgValue) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  return handleSynonymOrWildcardArgs();
}

// Abstraction (StmtSynonym, StmtNumber)
IntermediateTable StmtToStmtAbstraction ::evaluateSynonymInteger() {
  return handleSecondArgInteger();
}

// Abstraction (StmtSynonym, _)
IntermediateTable StmtToStmtAbstraction ::evaluateSynonymWildcard() {
  return handleSynonymOrWildcardArgs();
}

// Abstraction (StmtNumber, StmtSynonym)
IntermediateTable StmtToStmtAbstraction ::evaluateIntegerSynonym() {
  return handleFirstArgInteger();
}

// Abstraction (StmtNumber, StmtNumber)
IntermediateTable StmtToStmtAbstraction ::evaluateIntegerInteger() {
  return handleBothArgsInteger();
}

// Abstraction (StmtNumber, _)
IntermediateTable StmtToStmtAbstraction ::evaluateIntegerWildcard() {
  return handleFirstArgInteger();
}

// Abstraction (StmtNumber, StmtSynonym)
IntermediateTable StmtToStmtAbstraction ::evaluateWildcardSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Abstraction (_, StmtNumber)
IntermediateTable StmtToStmtAbstraction ::evaluateWildcardInteger() {
  return handleSecondArgInteger();
}

// Abstraction (_, _)
IntermediateTable StmtToStmtAbstraction ::evaluateWildcardWildcard() {
  return handleSynonymOrWildcardArgs();
}

IntermediateTable StmtToStmtAbstraction::handleSynonymOrWildcardArgs() {
  string firstArgStmtSynonym = this->firstArgValue;
  string secondArgStmtSynonym = this->secondArgValue;

  StmtType firstStmtType = this->getFirstArgStmtType();
  StmtType secondStmtType = this->getSecondArgStmtType();

  vector<pair<string, string>> stmtStmtPairs =
      (pkb.*getAllStmtStmtPairs)(firstStmtType, secondStmtType);

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      firstArgStmtSynonym, secondArgStmtSynonym, stmtStmtPairs);
}

IntermediateTable StmtToStmtAbstraction::handleBothArgsInteger() {
  string firstArgStmtNumberString = this->firstArgValue;
  string secondArgStmtNumberString = this->secondArgValue;

  if (firstArgStmtNumberString == secondArgStmtNumberString) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  int firstArgStmtNumber = stoi(firstArgStmtNumberString);
  int secondArgStmtNumber = stoi(secondArgStmtNumberString);

  bool isValid = (pkb.*isRelationTrue)(firstArgStmtNumber, secondArgStmtNumber);

  return isValid ? IntermediateTableFactory::buildWildcardIntermediateTable()
                 : IntermediateTableFactory::buildEmptyIntermediateTable();
}
