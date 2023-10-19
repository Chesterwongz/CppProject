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
  std::vector<std::string> allStmt = getAllStmtsOf(statementType);

  return std::find(allStmt.begin(), allStmt.end(),
                   std::to_string(statementNumber)) != allStmt.end();
}

bool DesignEntitiesReader::isValidConstant(std::string constantVal) {
  std::vector<std::string> allConstants = getAllConstants();

  return std::find(allConstants.begin(), allConstants.end(), constantVal) !=
         allConstants.end();
}

bool DesignEntitiesReader::isValidProc(std::string procName) {
  std::vector<std::string> allProcs = getAllProcedures();

  return std::find(allProcs.begin(), allProcs.end(), procName) !=
         allProcs.end();
}

bool DesignEntitiesReader::isValidVariable(std::string varName) {
  std::vector<std::string> allVariables = getAllVariables();

  return std::find(allVariables.begin(), allVariables.end(), varName) !=
         allVariables.end();
}

std::vector<std::string> DesignEntitiesReader::getStmtsThatCall(
    const std::string& procName) {
  auto callStmtFilter = stmtStore.getStmtFilterPredicate(StmtType::CALL);

  return CollectionUtils::transformIntToStrVector(
      callsSStore.getDirectAncestorsOf(procName, callStmtFilter));
}

std::vector<std::string> DesignEntitiesReader::getStmtsThatRead(
    const std::string& varName) {
  auto readStmtFilter = stmtStore.getStmtFilterPredicate(StmtType::READ);

  return CollectionUtils::transformIntToStrVector(
      modifiesSStore.getDirectAncestorsOf(varName, readStmtFilter));
}

std::vector<std::string> DesignEntitiesReader::getStmtsThatPrint(
    const std::string& varName) {
  auto printStmtFilter = stmtStore.getStmtFilterPredicate(StmtType::PRINT);

  return CollectionUtils::transformIntToStrVector(
      usesSStore.getDirectAncestorsOf(varName, printStmtFilter));
}

template <typename SStoreType>
std::string DesignEntitiesReader::getEntityBy(int statementNumber,
                                              StmtType stmtType,
                                              SStoreType& sStore) {
  if (isValidStmt(statementNumber, stmtType) &&
      sStore.hasDirectSuccessor(statementNumber)) {
    return *sStore.getDirectSuccessors(statementNumber).begin();
  }
  return "";
}

std::string DesignEntitiesReader::getProcCalledBy(int statementNumber) {
  return getEntityBy(statementNumber, StmtType::CALL, callsSStore);
}

std::string DesignEntitiesReader::getVariableReadBy(int statementNumber) {
  return getEntityBy(statementNumber, StmtType::READ, modifiesSStore);
}

std::string DesignEntitiesReader::getVariablePrintedBy(int statementNumber) {
  return getEntityBy(statementNumber, StmtType::PRINT, usesSStore);
}