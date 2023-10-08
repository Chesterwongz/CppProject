#include "UsesReader.h"

std::vector<std::string> UsesReader::getStatementsUsing(
    const std::string& variableName, StmtType statementType) {
  std::vector<std::string> result;

  std::set<int> statementNumbers =
      stmt_storage_.getStatementNumbersFromStatementType(statementType);

  for (int statementNumber : statementNumbers) {
    std::set<std::string> usedVariables =
        uses_storage_.getUsedVariablesForStatement(statementNumber);
    if (usedVariables.find(variableName) != usedVariables.end()) {
      result.emplace_back(std::to_string(statementNumber));
    }
  }

  return result;
}

std::vector<std::pair<std::string, std::string>> UsesReader::getVariablesUsedBy(
    int statementNumber, StmtType statementType) {
  std::vector<std::pair<std::string, std::string>> result;

  if (stmt_storage_.isStatementType(statementNumber, statementType)) {
    std::set<std::string> variables =
        uses_storage_.getUsedVariablesForStatement(statementNumber);

    for (const std::string& v : variables) {
      result.emplace_back(std::to_string(statementNumber), v);
    }
  }

  return result;
}

bool UsesReader::isVariableUsedBy(const std::string& variableName,
                                  const std::string& statementNumber) {
  std::vector<std::string> allStatementsUsing =
      getStatementsUsing(variableName, StmtType::STMT);
  return std::find(allStatementsUsing.begin(), allStatementsUsing.end(),
                   statementNumber) != allStatementsUsing.end();
}

std::vector<std::pair<std::string, std::string>>
UsesReader::getAllUsedVariables(StmtType statementType) {
  std::vector<std::pair<std::string, std::string>> result;
  std::set<std::string> variables = entity_storage_.getAllVariables();

  for (const std::string& v : variables) {
    std::set<int> statementNumbers =
        uses_storage_.getStatementNumbersForUsedVariable(v);

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
