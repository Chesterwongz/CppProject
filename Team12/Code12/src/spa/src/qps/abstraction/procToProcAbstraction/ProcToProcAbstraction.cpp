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
  return handleBothArgsIdent(firstArgValue, secondArgValue);
}

// Abstraction (ProcName, _)
IntermediateTable ProcToProcAbstraction::evaluateIdentWildcard() {
  return handleBothArgsIdent(firstArgValue, common::WILDCARD_PROC);
}

// Abstraction (_, Synonym)
IntermediateTable ProcToProcAbstraction::evaluateWildcardSynonym() {
  return handleFirstArgIdent(common::WILDCARD_PROC);
}

// Abstraction (_, ProcName)
IntermediateTable ProcToProcAbstraction::evaluateWildcardIdent() {
  return handleBothArgsIdent(common::WILDCARD_PROC, secondArgValue);
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
  TableDataType resultAsSynonymRes;
  if (SynResConversionUtils::isSynResCacheHit(this->signature)) {
    resultAsSynonymRes =
        SynResConversionUtils::getFromSynResCache(this->signature);
  } else {
    resultAsSynonymRes = SynResConversionUtils::toSynonymRes(
        allPairs, {PROCEDURE_ENTITY, PROCEDURE_ENTITY}, this->pkb);
    SynResConversionUtils::saveToSynResCache(this->signature,
                                             resultAsSynonymRes);
  }

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(colNames,
                                                          resultAsSynonymRes);
}

IntermediateTable ProcToProcAbstraction::handleFirstArgIdent(
    const string& firstArgProcName) {
  if (isSecondSynonymInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  string secondArgProcSynonym = this->secondArgValue;

  vector<string> possibleSecondProcs =
      getSecondProcInAbstraction(firstArgProcName);

  vector<std::reference_wrapper<SynonymRes>> resultAsSynonymRes;
  if (SynResConversionUtils::isSingleColSynResCacheHit(this->signature)) {
    resultAsSynonymRes =
        SynResConversionUtils::getFromSingleColSynResCache(this->signature);
  } else {
    resultAsSynonymRes = SynResConversionUtils::toSynonymRes(
        possibleSecondProcs, PROCEDURE_ENTITY, this->pkb);
    SynResConversionUtils::saveToSingleColSynResCache(this->signature,
                                                      resultAsSynonymRes);
  }

  return IntermediateTableFactory::buildSingleColTable(
      secondArgProcSynonym, std::move(resultAsSynonymRes));
}

IntermediateTable ProcToProcAbstraction::handleSecondArgIdent(
    const string& secondArgProcName) {
  if (isFirstSynonymInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }
  string firstArgSynonym = this->firstArgValue;

  vector<string> possibleFirstProcs =
      getFirstProcInAbstraction(secondArgProcName);

  vector<std::reference_wrapper<SynonymRes>> resultAsSynonymRes;
  if (SynResConversionUtils::isSingleColSynResCacheHit(this->signature)) {
    resultAsSynonymRes =
        SynResConversionUtils::getFromSingleColSynResCache(this->signature);
  } else {
    resultAsSynonymRes = SynResConversionUtils::toSynonymRes(
        possibleFirstProcs, PROCEDURE_ENTITY, this->pkb);
    SynResConversionUtils::saveToSingleColSynResCache(this->signature,
                                                      resultAsSynonymRes);
  }

  return IntermediateTableFactory::buildSingleColTable(
      firstArgSynonym, std::move(resultAsSynonymRes));
}

IntermediateTable ProcToProcAbstraction::handleBothArgsIdent(
    const string& firstArgProcName, const string& secondArgProcName) {
  if (firstArgProcName == secondArgProcName) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  bool isValid = isProcRelatedToProc(firstArgProcName, secondArgProcName);
  return isValid ? IntermediateTableFactory::buildWildcardIntermediateTable()
                 : IntermediateTableFactory::buildEmptyIntermediateTable();
}
