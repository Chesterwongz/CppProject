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
