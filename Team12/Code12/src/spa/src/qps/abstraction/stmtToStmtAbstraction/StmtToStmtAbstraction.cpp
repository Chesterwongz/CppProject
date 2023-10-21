#include "StmtToStmtAbstraction.h"

/**
 * StmtToStmtAbstraction abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

void StmtToStmtAbstraction::filterSelfRefPairs(
    vector<pair<string, string>>& stmtPairs) {
  if (!isSelfReferencePossible() ||
      this->firstArgValue != this->secondArgValue) {
    return;
  }
  stmtPairs.erase(std::remove_if(stmtPairs.begin(), stmtPairs.end(),
                                 [](const pair<string, string>& stmtPair) {
                                   return stmtPair.first != stmtPair.second;
                                 }),
                  stmtPairs.end());
}
// Self-reference (i.e. Abstraction (a, a) where a == a) not possible be default
bool StmtToStmtAbstraction::isSelfReferencePossible() { return false; }
bool StmtToStmtAbstraction::isFirstStmtTypeInvalid() { return false; }
bool StmtToStmtAbstraction::isSecondStmtTypeInvalid() { return false; }

// Abstraction (StmtSynonym, StmtSynonym)
IntermediateTable StmtToStmtAbstraction ::evaluateSynonymSynonym() {
  if (!isSelfReferencePossible() &&
      this->firstArgValue == this->secondArgValue) {
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
  if (!isSelfReferencePossible() &&
      this->firstArgValue == this->secondArgValue) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
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
  return handleBothArgsWildcard();
}

IntermediateTable StmtToStmtAbstraction::handleBothArgsWildcard() {
  StmtType firstStmtType = this->getFirstArgStmtType();
  StmtType secondStmtType = this->getSecondArgStmtType();

  vector<pair<string, string>> stmtStmtPairs =
      getAllPairs(firstStmtType, secondStmtType);

  if (stmtStmtPairs.empty()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  return IntermediateTableFactory::buildWildcardIntermediateTable();
}

IntermediateTable StmtToStmtAbstraction::handleSynonymOrWildcardArgs() {
  if (isFirstStmtTypeInvalid() || isSecondStmtTypeInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  string firstArgStmtSynonym = this->firstArgValue;
  string secondArgStmtSynonym = this->secondArgValue;

  StmtType firstStmtType = this->getFirstArgStmtType();
  StmtType secondStmtType = this->getSecondArgStmtType();

  vector<pair<string, string>> stmtStmtPairs =
      getAllPairs(firstStmtType, secondStmtType);

  filterSelfRefPairs(stmtStmtPairs);

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

  bool isValid = isStmtRelatedToStmt(firstArgStmtNumber, secondArgStmtNumber);

  return isValid ? IntermediateTableFactory::buildWildcardIntermediateTable()
                 : IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable StmtToStmtAbstraction::handleFirstArgInteger() {
  if (isSecondStmtTypeInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  int firstArgStmtNumber = stoi(this->firstArgValue);
  StmtType secondArgStmtType = this->getSecondArgStmtType();
  string secondStmtSynonym = this->secondArgValue;

  vector<string> results = getSecondStmt(firstArgStmtNumber, secondArgStmtType);

  return IntermediateTableFactory::buildSingleColTable(secondStmtSynonym,
                                                       results);
}
IntermediateTable StmtToStmtAbstraction::handleSecondArgInteger() {
  if (isFirstStmtTypeInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  string firstArgStmtSynonym = this->firstArgValue;
  StmtType firstArgStmtType = this->getFirstArgStmtType();
  int secondArgStmtNumber = stoi(this->secondArgValue);

  vector<string> results = getFirstStmt(secondArgStmtNumber, firstArgStmtType);

  return IntermediateTableFactory::buildSingleColTable(firstArgStmtSynonym,
                                                       results);
}
