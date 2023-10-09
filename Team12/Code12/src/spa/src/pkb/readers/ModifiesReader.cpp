#include "ModifiesReader.h"

std::vector<std::string> ModifiesReader::getStatementsModifying(
    const std::string& variableName, StmtType statementType) {
  std::vector<std::string> result;

  std::set<int> allMatchingStatements =
      stmt_storage_.getStatementNumbersFromStatementType(statementType);

  for (int statement : allMatchingStatements) {
    std::set<std::string> variables =
        modifies_storage_.getVarsModifiedByStmt(statement);

    if (variables.find(variableName) != variables.end()) {
      result.emplace_back(std::to_string(statement));
    }
  }

  return result;
}

std::vector<std::pair<std::string, std::string>>
ModifiesReader::getVariablesModifiedBy(int statementNumber,
                                       StmtType statementType) {
  std::vector<std::pair<std::string, std::string>> result;

  if (stmt_storage_.isStatementType(statementNumber, statementType)) {
    std::set<std::string> variables =
        modifies_storage_.getVarsModifiedByStmt(statementNumber);

    for (const std::string& v : variables) {
      result.emplace_back(std::to_string(statementNumber), v);
    }
  }

  return result;
}

bool ModifiesReader::isVariableModifiedBy(const std::string& variableName,
                                          const std::string& statementNumber) {
  std::vector<std::string> allStatementsModifying =
      getStatementsModifying(variableName, StmtType::STMT);
  return std::find(allStatementsModifying.begin(), allStatementsModifying.end(),
                   statementNumber) != allStatementsModifying.end();
}

std::vector<std::pair<std::string, std::string>>
ModifiesReader::getAllModifiedVariables(StmtType statementType) {
  std::vector<std::pair<std::string, std::string>> result;

  std::set<std::string> variables = entity_storage_.getAllVariables();

  for (const std::string& v : variables) {
    std::set<int> statementNumbers = modifies_storage_.getStmtsModifyingVar(v);

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
