#include "ProcToProcAbstraction.h"

#include <unordered_set>

#include "qps/abstraction/SynResConversionUtils.h"

/**
 * ProcToProcAbstraction abstraction:
 * - firstArg: Synonym (Proc) OR Identifier (Proc) OR Wildcard
 * - secondArg: Synonym (Proc) OR Identifier (Proc) OR Wildcard
 */

// Abstraction (Synonym, Synonym)
IntermediateTable ProcToProcAbstraction::evaluateSynonymSynonym() {
  if (this->firstArgValue == this->secondArgValue) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  return handleSynonymOrWildcardArgs();
}

// Abstraction (Synonym, ProcIdentifier)
IntermediateTable ProcToProcAbstraction::evaluateSynonymIdent() {
  return handleSecondArgIdent();
}

// Abstraction (Synonym, _)
IntermediateTable ProcToProcAbstraction::evaluateSynonymWildcard() {
  return handleSynonymOrWildcardArgs();
}

// Abstraction (ProcName, Synonym)
IntermediateTable ProcToProcAbstraction::evaluateIdentSynonym() {
  return handleFirstArgIdent();
}

// Abstraction (ProcName, ProcName)
IntermediateTable ProcToProcAbstraction::evaluateIdentIdent() {
  if (this->firstArgValue == this->secondArgValue) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  return handleBothArgsIdent();
}

// Abstraction (ProcName, _)
IntermediateTable ProcToProcAbstraction::evaluateIdentWildcard() {
  return handleFirstArgIdent();
}

// Abstraction (_, Synonym)
IntermediateTable ProcToProcAbstraction::evaluateWildcardSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Abstraction (_, ProcName)
IntermediateTable ProcToProcAbstraction::evaluateWildcardIdent() {
    return handleSecondArgIdent();
}

// Abstraction (_, _)
IntermediateTable ProcToProcAbstraction::evaluateWildcardWildcard() {
  return handleSynonymOrWildcardArgs();
}

IntermediateTable ProcToProcAbstraction::handleSynonymOrWildcardArgs() {
  string firstArgSynonym = this->firstArgValue;
  string secondArgSynonym = this->secondArgValue;

  assert(this->firstArg.isProcSynonym() || this->firstArg.isWildcard());
  assert(this->secondArg.isProcSynonym() || this->secondArg.isWildcard());

  vector<pair<string, string>> allPairs = getAllAbstractionPairs();

  pair<Entity, Entity> entityPair = {getArgEntity(this->firstArg),
                                     getArgEntity(this->secondArg)};
  vector<string> colNames = {firstArgSynonym, secondArgSynonym};
  TableDataType resultAsSynonymRes = SynResConversionUtils::toSynonymRes(
      allPairs, entityPair, this->pkb);


  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      colNames, resultAsSynonymRes);
}

IntermediateTable ProcToProcAbstraction::handleFirstArgIdent() {
  string firstArgProcName = this->firstArgValue;
  string secondArgProcSynonym = this->secondArgValue;
  assert(this->secondArg.isProcSynonym() || this->secondArg.isWildcard());
  vector<string> possibleSecondProcs =
      getSecondProcInAbstraction(firstArgProcName);
  return IntermediateTableFactory::buildSingleColTable(secondArgProcSynonym,
                                                       possibleSecondProcs);
}

IntermediateTable ProcToProcAbstraction::handleSecondArgIdent() {
  string firstArgSynonym = this->firstArgValue;
  assert(this->firstArg.isProcSynonym() || this->firstArg.isWildcard());
  string secondArgProcName = this->secondArgValue;

  vector<string> possibleValuesOfSynonym =
      getFirstProcInAbstraction(secondArgProcName);
  return IntermediateTableFactory::buildSingleColTable(firstArgSynonym,
                                                       possibleValuesOfSynonym);
}

IntermediateTable ProcToProcAbstraction::handleBothArgsIdent() {
  string firstArgProcName = this->firstArgValue;
  string secondArgProcName = this->secondArgValue;
  if (firstArgProcName == secondArgProcName) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  bool isValid = isProcRelatedToProc(firstArgProcName, secondArgProcName);

  return isValid ? IntermediateTableFactory::buildWildcardIntermediateTable()
                 : IntermediateTableFactory::buildEmptyIntermediateTable();
}
