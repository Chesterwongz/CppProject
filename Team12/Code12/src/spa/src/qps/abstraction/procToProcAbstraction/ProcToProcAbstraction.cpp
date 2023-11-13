#include "ProcToProcAbstraction.h"

#include <unordered_set>

#include "qps/clause/utils/ClauseUtil.h"

/**
 * ProcToProcAbstraction abstraction:
 * - firstArg: Synonym (Proc) OR Identifier (Proc) OR Wildcard
 * - secondArg: Synonym (Proc) OR Identifier (Proc) OR Wildcard
 */

bool ProcToProcAbstraction::isFirstSynonymInvalid() {
  bool isNotProcOrWildcard =
      !(this->firstArg.isProcSynonym() || this->firstArg.isWildcard());
  return isNotProcOrWildcard;
}

bool ProcToProcAbstraction::isSecondSynonymInvalid() {
  bool isNotProcOrWildcard =
      !(this->secondArg.isProcSynonym() || this->secondArg.isWildcard());
  return isNotProcOrWildcard;
}

// Abstraction (Synonym, Synonym)
IntermediateTable ProcToProcAbstraction::evaluateSynonymSynonym() {
  if (this->firstArgValue == this->secondArgValue) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  return handleSynonymOrWildcardArgs();
}

// Abstraction (Synonym, ProcIdentifier)
IntermediateTable ProcToProcAbstraction::evaluateSynonymIdent() {
  return handleSecondArgIdent(secondArgValue);
}

// Abstraction (Synonym, _)
IntermediateTable ProcToProcAbstraction::evaluateSynonymWildcard() {
  return handleSecondArgIdent(common::WILDCARD_PROC);
}

// Abstraction (ProcName, Synonym)
IntermediateTable ProcToProcAbstraction::evaluateIdentSynonym() {
  return handleFirstArgIdent(firstArgValue);
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
  return handleFirstArgIdent(firstArgValue);
}

// Abstraction (_, Synonym)
IntermediateTable ProcToProcAbstraction::evaluateWildcardSynonym() {
  return handleFirstArgIdent(common::WILDCARD_PROC);
}

// Abstraction (_, ProcName)
IntermediateTable ProcToProcAbstraction::evaluateWildcardIdent() {
  return handleSecondArgIdent(secondArgValue);
}

// Abstraction (_, _)
IntermediateTable ProcToProcAbstraction::evaluateWildcardWildcard() {
  return this->hasPairs()
             ? IntermediateTableFactory::buildWildcardIntermediateTable()
             : IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable ProcToProcAbstraction::handleSynonymOrWildcardArgs() {
  if (isFirstSynonymInvalid() || isSecondSynonymInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  string firstArgSynonym = this->firstArgValue;
  string secondArgSynonym = this->secondArgValue;

  vector<pair<string, string>> allPairs = getAllAbstractionPairs();

  vector<string> colNames = {firstArgSynonym, secondArgSynonym};
  TableDataType resultAsSynonymRes = SynResConversionUtils::toSynonymRes(
      allPairs, {PROCEDURE_ENTITY, PROCEDURE_ENTITY}, this->pkb);

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(colNames,
                                                          resultAsSynonymRes);
}

IntermediateTable ProcToProcAbstraction::handleFirstArgIdent(const string& firstArgProcName) {
  if (isSecondSynonymInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  string secondArgProcSynonym = this->secondArgValue;

  vector<string> possibleSecondProcs =
      getSecondProcInAbstraction(firstArgProcName);
  vector<std::reference_wrapper<SynonymRes>> resultAsSynonymRes =
      SynResConversionUtils::toSynonymRes(possibleSecondProcs, PROCEDURE_ENTITY,
                                          this->pkb);

  return IntermediateTableFactory::buildSingleColTable(secondArgProcSynonym,
                                                       resultAsSynonymRes);
}

IntermediateTable ProcToProcAbstraction::handleSecondArgIdent(const string& secondArgProcName) {
  if (isFirstSynonymInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  string firstArgSynonym = this->firstArgValue;

  vector<string> possibleFirstProcs =
      getFirstProcInAbstraction(secondArgProcName);
  vector<std::reference_wrapper<SynonymRes>> resultAsSynonymRes =
      SynResConversionUtils::toSynonymRes(possibleFirstProcs, PROCEDURE_ENTITY,
                                          this->pkb);

  return IntermediateTableFactory::buildSingleColTable(firstArgSynonym,
                                                       resultAsSynonymRes);
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
