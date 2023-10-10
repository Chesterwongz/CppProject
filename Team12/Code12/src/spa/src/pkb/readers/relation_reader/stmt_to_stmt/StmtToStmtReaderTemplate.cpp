#include "StmtToStmtReaderTemplate.h"

std::vector<std::string>
StmtToStmtReaderTemplate::getStmtsRelatedToVarByStmtType(
    const std::string& varName, StmtType stmtType) {
  std::vector<std::string> result;

  std::set<int> allMatchingStatements =
      stmt_storage_.getStatementNumbersFromStatementType(stmtType);

  for (int statement : allMatchingStatements) {
    std::set<std::string> variables = getVarsRelatedToStmt(statement);

    if (variables.find(varName) != variables.end()) {
      result.emplace_back(std::to_string(statement));
    }
  }

  return result;
}
std::vector<std::pair<std::string, std::string>>
StmtToStmtReaderTemplate::getVarsRelatedToStmtByStmtType(
    int stmtNum, StmtType stmtType) {
  std::vector<std::pair<std::string, std::string>> result;

  if (stmt_storage_.isStatementType(stmtNum, stmtType)) {
    std::set<std::string> variables = getVarsRelatedToStmt(stmtNum);

    for (const std::string& v : variables) {
      result.emplace_back(std::to_string(stmtNum), v);
    }
  }

  return result;
}
bool StmtToStmtReaderTemplate::isVarRelatedToStmt(
    const std::string& varName, const std::string& stmtNumStr) {
  std::vector<std::string> allStatementsModifying =
      getStmtsRelatedToVarByStmtType(varName, StmtType::STMT);
  return std::find(allStatementsModifying.begin(), allStatementsModifying.end(),
                   stmtNumStr) != allStatementsModifying.end();
}

std::vector<std::pair<std::string, std::string>>
StmtToStmtReaderTemplate::getAllRelationsByStmtType(
    StmtType statementType) {
  std::vector<std::pair<std::string, std::string>> result;

  std::set<std::string> variables = entity_storage_.getAllVariables();

  for (const std::string& v : variables) {
    std::set<int> statementNumbers = getStmtsRelatedToVar(v);

    for (int stmt : statementNumbers) {
      std::set<int> sameStatementType =
          stmt_storage_.getStatementNumbersFromStatementType(statementType);
      if (sameStatementType.find(stmt) != sameStatementType.end()) {
        result.emplace_back(std::to_string(stmt), v);
      }
    }
  }

  return result;
}
