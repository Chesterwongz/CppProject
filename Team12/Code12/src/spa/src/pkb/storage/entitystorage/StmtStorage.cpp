#include "StmtStorage.h"

void StmtStorage::setStatement(int statementNumber,
                                    StmtType statementType) {
  statements[statementType].insert(statementNumber);
}

std::set<int> StmtStorage::getAllStatements() {
  std::set<int> allStatements;

  for (const auto& entry : statements) {
    const std::set<int>& statementSet = entry.second;
    allStatements.insert(statementSet.begin(), statementSet.end());
  }

  return allStatements;
}

std::set<int> StmtStorage::getStatementNumbersFromStatementType(
    StmtType statementType) {
  if (statementType == StmtType::STMT) {
    return getAllStatements();
  }
  return statements[statementType];
}

StmtType StmtStorage::getStatementTypeFromStatementNumber(
    int statementNumber) {
  for (const auto& entry : statements) {
    const std::set<int>& statementNumbers = entry.second;
    if (statementNumbers.find(statementNumber) != statementNumbers.end()) {
      return entry.first;
    }
  }
  return StmtType::INVALID;
}

bool StmtStorage::isStatementType(int statementNumber,
                                       StmtType statementType) {
  return statementType == StmtType::STMT ||
         getStatementTypeFromStatementNumber(statementNumber) == statementType;
}
