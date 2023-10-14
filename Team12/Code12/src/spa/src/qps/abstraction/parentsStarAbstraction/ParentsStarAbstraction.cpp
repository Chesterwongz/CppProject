#include "ParentsStarAbstraction.h"

/**
 * Parents star abstraction:
 * firstArg: Synonym OR Integer OR Wildcard
 * secondArg: Synonym OR Integer OR Wildcard
 */

// Parents* (StmtSynonym, StmtSynonym)
IntermediateTable ParentsStarAbstraction::evaluateSynonymSynonym() {
  if (this->firstArgValue == this->secondArgValue) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  return handleSynonymOrWildcardArgs();
}

// Parents* (StmtSynonym, StmtNumber)
IntermediateTable ParentsStarAbstraction::evaluateSynonymInteger() {
  return handleSecondArgInteger();
}

// Parents* (StmtSynonym, _)
IntermediateTable ParentsStarAbstraction::evaluateSynonymWildcard() {
  return handleSynonymOrWildcardArgs();
}

// Parents* (StmtNumber, StmtSynonym)
IntermediateTable ParentsStarAbstraction::evaluateIntegerSynonym() {
  return handleFirstArgInteger();
}

// Parents* (StmtNumber, StmtNumber)
IntermediateTable ParentsStarAbstraction::evaluateIntegerInteger() {
  return handleBothArgsInteger();
}

// Parents* (StmtNumber, _)
IntermediateTable ParentsStarAbstraction::evaluateIntegerWildcard() {
  return handleFirstArgInteger();
}

// Parents* (_, StmtSynonym)
IntermediateTable ParentsStarAbstraction::evaluateWildcardSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Parents* (_, StmtNumber)
IntermediateTable ParentsStarAbstraction::evaluateWildcardInteger() {
  return handleSecondArgInteger();
}

// Parents* (_, _)
IntermediateTable ParentsStarAbstraction::evaluateWildcardWildcard() {
  return handleSynonymOrWildcardArgs();
}

/**
 * For handling cases where both args are non-integer
 */
IntermediateTable ParentsStarAbstraction::handleSynonymOrWildcardArgs() {
  string firstArgStmtSynonym = this->firstArgValue;
  StmtType firstStmtType = this->getFirstArgStmtType();
  string secondArgStmtSynonym = this->secondArgValue;
  StmtType secondArgStmtNumber = this->getSecondArgStmtType();

  vector<pair<string, string>> parentChildPairs =
      pkb.getParentChildStarPairs(firstStmtType, secondArgStmtNumber);

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      firstArgStmtSynonym, secondArgStmtSynonym, parentChildPairs);
}

IntermediateTable ParentsStarAbstraction::handleBothArgsInteger() {
  if (this->firstArgValue == this->secondArgValue) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  int firstArgStmtNumber = stoi(this->firstArgValue);
  int secondArgStmtNumber = stoi(this->secondArgValue);

  bool isValid = pkb.isParentStar(firstArgStmtNumber, secondArgStmtNumber);

  return isValid ? IntermediateTableFactory::buildWildcardIntermediateTable()
                 : IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable ParentsStarAbstraction::handleFirstArgInteger() {
  int firstArgStmtNumber = stoi(this->firstArgValue);
  StmtType secondArgStmtType = this->getSecondArgStmtType();
  string secondStmtSynonym = this->secondArgValue;

  vector<string> results =
      pkb.getChildrenStarOf(firstArgStmtNumber, secondArgStmtType);

  // pass first col as wildcard so the table ignores integer column
  return IntermediateTableFactory::buildSingleColTable(secondStmtSynonym,
                                                       results);
}

IntermediateTable ParentsStarAbstraction::handleSecondArgInteger() {
  string firstArgStmtSynonym = this->firstArgValue;
  StmtType firstArgStmtType = this->getFirstArgStmtType();
  int secondArgStmtNumber = stoi(this->secondArgValue);

  vector<string> results =
      pkb.getParentStarOf(secondArgStmtNumber, firstArgStmtType);

  // pass second col as wildcard so the table ignores the integer column
  return IntermediateTableFactory::buildSingleColTable(firstArgStmtSynonym,
                                                       results);
}
