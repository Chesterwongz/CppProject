#include "StmtToStmtAbstraction.h"

#include "qps/clause/utils/ClauseUtil.h"

/**
 * StmtToStmtAbstraction abstraction:
 * - firstArg: Synonym OR Integer OR Wildcard
 * - secondArg: Synonym OR Integer OR Wildcard
 */

vector<string> StmtToStmtAbstraction::filterSelfRefPairs(
    vector<pair<string, string>>& stmtPairs) {
  vector<string> filteredRes {};
  for (const auto& [firstArg, secondArg] : stmtPairs) {
    if (firstArg == secondArg) {
      filteredRes.emplace_back(firstArg);
    }
  }
  return filteredRes;
}
// Self-reference (i.e. Abstraction (a, a) where a == a) not possible be default
bool StmtToStmtAbstraction::isSelfReferencePossible() { return false; }
bool StmtToStmtAbstraction::isFirstSynonymInvalid() {
  bool isNotStmtOrWildcard =
      !(this->firstArg.isStmtSynonym() || this->firstArg.isWildcard());
  return isNotStmtOrWildcard;
}
bool StmtToStmtAbstraction::isSecondSynonymInvalid() {
  bool isNotStmtOrWildcard =
      !(this->secondArg.isStmtSynonym() || this->secondArg.isWildcard());
  return isNotStmtOrWildcard;
}

// Abstraction (StmtSynonym, StmtSynonym)
IntermediateTable StmtToStmtAbstraction ::evaluateSynonymSynonym() {
  return handleSynonymOrWildcardArgs();
}

// Abstraction (StmtSynonym, StmtNumber)
IntermediateTable StmtToStmtAbstraction ::evaluateSynonymInteger() {
  return handleSecondArgInteger(stoi(secondArgValue));
}

// Abstraction (StmtSynonym, _)
IntermediateTable StmtToStmtAbstraction ::evaluateSynonymWildcard() {
  return handleSecondArgInteger(common::WILDCARD_STMT_NUM);
}

// Abstraction (StmtNumber, StmtSynonym)
IntermediateTable StmtToStmtAbstraction ::evaluateIntegerSynonym() {
  return handleFirstArgInteger(stoi(firstArgValue));
}

// Abstraction (StmtNumber, StmtNumber)
IntermediateTable StmtToStmtAbstraction ::evaluateIntegerInteger() {
  return handleBothArgsInteger(stoi(firstArgValue), stoi(secondArgValue));
}

// Abstraction (StmtNumber, _)
IntermediateTable StmtToStmtAbstraction ::evaluateIntegerWildcard() {
  return handleBothArgsInteger(stoi(firstArgValue), common::WILDCARD_STMT_NUM);
}

// Abstraction (_, StmtSynonym)
IntermediateTable StmtToStmtAbstraction ::evaluateWildcardSynonym() {
  return handleFirstArgInteger(common::WILDCARD_STMT_NUM);
}

// Abstraction (_, StmtNumber)
IntermediateTable StmtToStmtAbstraction ::evaluateWildcardInteger() {
  return handleBothArgsInteger(common::WILDCARD_STMT_NUM, stoi(secondArgValue));
}

// Abstraction (_, _)
IntermediateTable StmtToStmtAbstraction ::evaluateWildcardWildcard() {
  return this->hasPairs()
             ? IntermediateTableFactory::buildWildcardIntermediateTable()
             : IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable StmtToStmtAbstraction::handleSynonymOrWildcardArgs() {
  const string& firstArgStmtSynonym = this->firstArgValue;
  const string& secondArgStmtSynonym = this->secondArgValue;
  if (isFirstSynonymInvalid() || isSecondSynonymInvalid() ||
      (!isSelfReferencePossible() &&
       firstArgStmtSynonym == secondArgStmtSynonym)) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  StmtType firstStmtType = this->getFirstArgStmtType();
  StmtType secondStmtType = this->getSecondArgStmtType();

  vector<pair<string, string>> stmtStmtPairs =
      getAllPairs(firstStmtType, secondStmtType);

  if (isSelfReferencePossible() &&
      firstArgStmtSynonym == secondArgStmtSynonym) {
    vector<string> filteredRes = filterSelfRefPairs(stmtStmtPairs);
    vector<std::reference_wrapper<SynonymRes>> resultAsSynonymRes =
        SynResConversionUtils::toSynonymRes(
            filteredRes, ClauseUtil::getArgEntity(this->firstArg), this->pkb);
    return IntermediateTableFactory::buildSingleColTable(firstArgStmtSynonym,
                                                         resultAsSynonymRes);
  }

  pair<Entity, Entity> entityPair = {ClauseUtil::getArgEntity(this->firstArg),
                                     ClauseUtil::getArgEntity(this->secondArg)};
  vector<string> colNames = {firstArgStmtSynonym, secondArgStmtSynonym};
  TableDataType resultAsSynonymRes;
  if (SynResConversionUtils::isSynResCacheHit(this->signature)) {
    resultAsSynonymRes = SynResConversionUtils::getFromSynResCache(signature);
  } else {
    resultAsSynonymRes = SynResConversionUtils::toSynonymRes(
        stmtStmtPairs, entityPair, this->pkb);
    SynResConversionUtils::saveToSynResCache(this->signature,
                                             resultAsSynonymRes);
  }

  //! If any of the args are "_", the column will be ignored.
  return IntermediateTableFactory::buildIntermediateTable(
      colNames, std::move(resultAsSynonymRes));
}

IntermediateTable StmtToStmtAbstraction::handleBothArgsInteger(int s1, int s2) {
  if (!isSelfReferencePossible() && s1 == s2) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  bool isValid = isStmtRelatedToStmt(s1, s2);

  return isValid ? IntermediateTableFactory::buildWildcardIntermediateTable()
                 : IntermediateTableFactory::buildEmptyIntermediateTable();
}

IntermediateTable StmtToStmtAbstraction::handleFirstArgInteger(int stmt) {
  if (isSecondSynonymInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  StmtType secondArgStmtType = this->getSecondArgStmtType();
  string secondStmtSynonym = this->secondArgValue;

  vector<string> results = getSecondStmt(stmt, secondArgStmtType);

  Entity secondArgEntity = ClauseUtil::getArgEntity(this->secondArg);
  vector<std::reference_wrapper<SynonymRes>> resultAsSynonymRes;
  if (SynResConversionUtils::isSingleColSynResCacheHit(this->signature)) {
    resultAsSynonymRes =
        SynResConversionUtils::getFromSingleColSynResCache(this->signature);
  } else {
    resultAsSynonymRes = SynResConversionUtils::toSynonymRes(
        results, secondArgEntity, this->pkb);
    SynResConversionUtils::saveToSingleColSynResCache(this->signature,
                                                      resultAsSynonymRes);
  }

  return IntermediateTableFactory::buildSingleColTable(
      secondStmtSynonym, std::move(resultAsSynonymRes));
}

IntermediateTable StmtToStmtAbstraction::handleSecondArgInteger(int stmt) {
  if (isFirstSynonymInvalid()) {
    return IntermediateTableFactory::buildEmptyIntermediateTable();
  }

  const string& firstArgStmtSynonym = this->firstArgValue;
  StmtType firstArgStmtType = this->getFirstArgStmtType();

  vector<string> results = getFirstStmt(stmt, firstArgStmtType);

  Entity firstArgEntity = ClauseUtil::getArgEntity(this->firstArg);

  vector<std::reference_wrapper<SynonymRes>> resultAsSynonymRes;
  if (SynResConversionUtils::isSingleColSynResCacheHit(this->signature)) {
    resultAsSynonymRes =
        SynResConversionUtils::getFromSingleColSynResCache(signature);
  } else {
    resultAsSynonymRes =
        SynResConversionUtils::toSynonymRes(results, firstArgEntity, this->pkb);
    SynResConversionUtils::saveToSingleColSynResCache(this->signature,
                                                      resultAsSynonymRes);
  }

  return IntermediateTableFactory::buildSingleColTable(
      firstArgStmtSynonym, std::move(resultAsSynonymRes));
}
