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
  return CollectionUtils::unorderedSetUToVectorV<int, std::string>(
      stmtSet, StringUtils::intToStrMapper);
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

// std::string DesignEntitiesReader::getProcCalledBy(int statementNumber) {
//   std::vector<std::string> callStmts = getAllStmtsOf(StmtType::CALL);
//   std::vector<std::string> results =
//       callsSStore.getAllDirectSuccessorsOf(statementNumber);
//
//   if (results.empty() ||
//       std::find(callStmts.begin(), callStmts.end(),
//                 std::to_string(statementNumber)) == callStmts.end()) {
//     return "";
//   }
//   return results.front();
// }

std::vector<std::string> DesignEntitiesReader::getStmtsThatRead(
    const std::string& varName) {
  auto readStmtFilter = stmtStore.getStmtFilterPredicate(StmtType::READ);

  return CollectionUtils::transformIntToStrVector(
      modifiesSStore.getDirectAncestorsOf(varName, readStmtFilter));
}

// std::string DesignEntitiesReader::getVariableReadBy(int statementNumber) {
//   std::vector<std::string> readStmts = getAllStmtsOf(StmtType::READ);
//   std::vector<std::string> results =
//       modifiesSStore.getAllDirectSuccessorsOf(statementNumber);
//
//   if (results.empty() ||
//       std::find(readStmts.begin(), readStmts.end(),
//                 std::to_string(statementNumber)) == readStmts.end()) {
//     return "";
//   }
//   return results.front();
// }

std::vector<std::string> DesignEntitiesReader::getStmtsThatPrint(
    const std::string& varName) {
  auto printStmtFilter = stmtStore.getStmtFilterPredicate(StmtType::PRINT);

  return CollectionUtils::transformIntToStrVector(
      usesSStore.getDirectAncestorsOf(varName, printStmtFilter));
}

std::string DesignEntitiesReader::getVariablePrintedBy(int statementNumber) {
  bool isValid = isValidStmt(statementNumber, StmtType::CALL);

  std::vector<std::string> printStmts = getAllStmtsOf(StmtType::PRINT);

  std::vector<std::string> results =
      usesSStore.getAllDirectSuccessorsOf(statementNumber);

  if (results.empty() ||
      std::find(printStmts.begin(), printStmts.end(),
                std::to_string(statementNumber)) == printStmts.end()) {
    return "";
  }
  return results.front();
}

template <typename SStoreType>
std::string DesignEntitiesReader::getEntityBy(int statementNumber,
                                              StmtType stmtType,
                                              SStoreType& sStore) {
  if (stmtStore.is()) std::vector<std::string> stmts = getAllStmtsOf(stmtType);
  std::vector<std::string> results =
      sStore.getAllDirectSuccessorsOf(statementNumber);

  if (results.empty() ||
      std::find(stmts.begin(), stmts.end(), std::to_string(statementNumber)) ==
          stmts.end()) {
    return "";
  }
  return results.front();
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