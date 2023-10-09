#include "DesignEntitiesReader.h"

std::set<std::string> DesignEntitiesReader::getAllVariables() {
  return entity_storage_.getAllVariables();
}

std::set<std::string> DesignEntitiesReader::getAllConstants() {
  return entity_storage_.getAllConstants();
}

std::set<std::string> DesignEntitiesReader::getAllProcedures() {
  return entity_storage_.getAllProcedures();
}

std::set<std::string> DesignEntitiesReader::getStatement(
    StmtType statementType) {
  std::set<std::string> result;

  std::set<int> temp =
      stmt_storage_.getStatementNumbersFromStatementType(statementType);
  for (int stmt : temp) {
    result.insert(std::to_string(stmt));
  }
  return result;
}

std::string DesignEntitiesReader::getProcFromStmt(int stmtNum) {
  return entity_storage_.getProcFromStmt(stmtNum);
}
