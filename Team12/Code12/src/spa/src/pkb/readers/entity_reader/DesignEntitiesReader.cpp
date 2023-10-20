#include "DesignEntitiesReader.h"

std::vector<std::string> DesignEntitiesReader::getAllVariables() {
  const auto& varSet = entityStore.getAllVars();
  return {varSet.begin(), varSet.end()};
}

std::vector<std::string> DesignEntitiesReader::getAllConstants() {
  const auto& constSet = entityStore.getAllConsts();
  return {constSet.begin(), constSet.end()};
}

std::vector<std::string> DesignEntitiesReader::getAllProcedures() {
  const auto& procSet = entityStore.getAllProcs();
  return {procSet.begin(), procSet.end()};
}

std::vector<std::string> DesignEntitiesReader::getAllStmtsOf(
    StmtType statementType) {
  if (!stmtStore.hasStmtType(statementType)) {
    return {};
  }
  const auto& stmtSet = stmtStore.getAllStmtsOf(statementType);
  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      stmtSet, CollectionUtils::intToStrMapper);
}

bool DesignEntitiesReader::isValidStmt(int statementNumber,
                                       StmtType statementType) {
  return stmtStore.hasStmt(statementNumber, statementType);
}

bool DesignEntitiesReader::isValidConstant(std::string constantVal) {
  return entityStore.hasConst(constantVal);
}

bool DesignEntitiesReader::isValidProc(std::string procName) {
  return entityStore.hasProc(procName);
}

bool DesignEntitiesReader::isValidVariable(std::string varName) {
  return entityStore.hasVariable(varName);
}

std::vector<std::string> DesignEntitiesReader::getStmtsThatCall(
    const std::string& procName) {
  if (!callsSStore.hasDirectAncestors(procName)) {
    return {};
  }

  const std::unordered_set<int>& result =
      callsSStore.getDirectAncestors(procName);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      result, CollectionUtils::intToStrMapper);
}

std::vector<std::string> DesignEntitiesReader::getStmtsThatRead(
    const std::string& varName) {
  if (!stmtStore.hasStmtType(StmtType::READ) ||
      !modifiesSStore.hasDirectAncestors(varName)) {
    return {};
  }
  auto stmtFilter = stmtStore.getStmtFilterPredicate(StmtType::READ);

  const auto& rawRes = modifiesSStore.getDirectAncestors(varName);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, stmtFilter);
}

std::vector<std::string> DesignEntitiesReader::getStmtsThatPrint(
    const std::string& varName) {
  if (!stmtStore.hasStmtType(StmtType::PRINT) ||
      !usesSStore.hasDirectAncestors(varName)) {
    return {};
  }

  auto printStmtFilter = stmtStore.getStmtFilterPredicate(StmtType::PRINT);

  const auto& rawRes = usesSStore.getDirectAncestors(varName);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      rawRes, CollectionUtils::intToStrMapper, printStmtFilter);
}

template <typename SStoreType>
std::vector<std::string> DesignEntitiesReader::getEntityBy(int statementNumber,
                                                           StmtType stmtType,
                                                           SStoreType& sStore) {
  std::vector<std::string> result;
  if (isValidStmt(statementNumber, stmtType) &&
      sStore.hasDirectSuccessors(statementNumber)) {
    const auto& rawRes = sStore.getDirectSuccessors(statementNumber);
    result = {rawRes.begin(), rawRes.end()};
  }
  return result;
}

std::vector<std::string> DesignEntitiesReader::getProcCalledBy(
    int statementNumber) {
  return getEntityBy(statementNumber, StmtType::CALL, callsSStore);
}

std::vector<std::string> DesignEntitiesReader::getVariableReadBy(
    int statementNumber) {
  return getEntityBy(statementNumber, StmtType::READ, modifiesSStore);
}

std::vector<std::string> DesignEntitiesReader::getVariablePrintedBy(
    int statementNumber) {
  return getEntityBy(statementNumber, StmtType::PRINT, usesSStore);
}
