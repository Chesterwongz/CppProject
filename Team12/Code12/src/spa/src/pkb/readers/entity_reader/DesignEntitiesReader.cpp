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
  if (!callsSStore.hasDirectAncestor(procName)) {
    return {};
  }

  const std::unordered_set<int>& result =
      callsSStore.getDirectAncestors(procName);

  return CollectionUtils::transformSetUToVectorV<int, std::string>(
      result, CollectionUtils::intToStrMapper);
}

std::vector<std::string> DesignEntitiesReader::getStmtsThatRead(
    const std::string& varName) {
  if (!stmtStore.hasStmtType(StmtType::READ)) {
    return {};
  }

  auto readStmtFilter = stmtStore.getStmtFilterPredicate(StmtType::READ);

  return CollectionUtils::transformIntToStrVector(
      modifiesSStore.getDirectAncestorsOf(varName, readStmtFilter));
}

std::vector<std::string> DesignEntitiesReader::getStmtsThatPrint(
    const std::string& varName) {
  if (!stmtStore.hasStmtType(StmtType::PRINT)) {
    return {};
  }

  auto printStmtFilter = stmtStore.getStmtFilterPredicate(StmtType::PRINT);

  return CollectionUtils::transformIntToStrVector(
      usesSStore.getDirectAncestorsOf(varName, printStmtFilter));
}

template <typename SStoreType>
std::vector<std::string> DesignEntitiesReader::getEntityBy(int statementNumber,
                                                           StmtType stmtType,
                                                           SStoreType& sStore) {
  std::vector<std::string> result;
  if (isValidStmt(statementNumber, stmtType) &&
      sStore.hasDirectSuccessor(statementNumber)) {
    result = {sStore.getDirectSuccessors(statementNumber).begin(),
              sStore.getDirectSuccessors(statementNumber).end()};
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

std::vector<std::pair<std::string, std::string>>
DesignEntitiesReader::getAllStmtProcCallsPairs() {
  return CollectionUtils::transformIntStrToStrStrVector(
      callsSStore.getAllDirectRelations());
}

std::vector<std::pair<std::string, std::string>>
DesignEntitiesReader::getAllStmtVarReadPairs() {
  std::vector<std::pair<std::string, std::string>> result;
  std::vector<std::string> allReadStmts = getAllStmtsOf(StmtType::READ);
  for (const std::string& stmt : allReadStmts) {
    std::string variableRead = getVariableReadBy(stoi(stmt)).front();
    result.emplace_back(stmt, variableRead);
  }
  return result;
}

std::vector<std::pair<std::string, std::string>>
DesignEntitiesReader::getAllStmtVarPrintPairs() {
  std::vector<std::pair<std::string, std::string>> result;
  std::vector<std::string> allPrintStmts = getAllStmtsOf(StmtType::PRINT);
  for (const std::string& stmt : allPrintStmts) {
    std::string variablePrinted = getVariablePrintedBy(stoi(stmt)).front();
    result.emplace_back(stmt, variablePrinted);
  }
  return result;
}