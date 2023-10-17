#include "StmtOrProcToVarReaderTemplate.h"

std::vector<std::string>
StmtOrProcToVarReaderTemplate::getStmtsRelatedToVarByStmtType(
    const std::string& varName, StmtType stmtType) {
  std::vector<std::string> result;

  std::unordered_set<int> allMatchingStatements =
      stmtStore.getAllStmtsOf(stmtType);

  for (int statement : allMatchingStatements) {
    std::set<std::string> variables = getVarsRelatedToStmt(statement);

    if (variables.find(varName) != variables.end()) {
      result.emplace_back(std::to_string(statement));
    }
  }

  return result;
}
std::vector<std::pair<std::string, std::string>>
StmtOrProcToVarReaderTemplate::getVarsRelatedToStmtByStmtType(
    int stmtNum, StmtType stmtType) {
  std::vector<std::pair<std::string, std::string>> result;

  if (stmtStore.isStmtType(stmtNum, stmtType)) {
    std::set<std::string> variables = getVarsRelatedToStmt(stmtNum);

    for (const std::string& v : variables) {
      result.emplace_back(std::to_string(stmtNum), v);
    }
  }

  return result;
}
bool StmtOrProcToVarReaderTemplate::isVarRelatedToStmt(
    const std::string& varName, const std::string& stmtNumStr) {
  std::vector<std::string> allStatementsModifying =
      getStmtsRelatedToVarByStmtType(varName, StmtType::STMT);
  return std::find(allStatementsModifying.begin(), allStatementsModifying.end(),
                   stmtNumStr) != allStatementsModifying.end();
}

std::vector<std::pair<std::string, std::string>>
StmtOrProcToVarReaderTemplate::getAllRelationsByStmtType(
    StmtType statementType) {
  std::vector<std::pair<std::string, std::string>> result;

  std::set<std::string> variables = entity_storage_.getAllVariables();

  for (const std::string& v : variables) {
    std::set<int> statementNumbers = getStmtsRelatedToVar(v);

    for (int stmt : statementNumbers) {
      std::unordered_set<int> sameStatementType =
          stmtStore.getAllStmtsOf(statementType);
      if (sameStatementType.find(stmt) != sameStatementType.end()) {
        result.emplace_back(std::to_string(stmt), v);
      }
    }
  }

  return result;
}
