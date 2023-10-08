#include "UsesModifiesStorage.h"

void UsesModifiesStorage::setVariableModification(
    const std::string& variableName, int statementNumber) {
  modifies_storage_.setVariableModification(variableName, statementNumber);
}

std::set<std::string> UsesModifiesStorage::getModifiedVariablesForStatement(
    int statementNumber) {
  return modifies_storage_.getVariablesForStatement(statementNumber);
}

std::set<int> UsesModifiesStorage::getStatementNumbersForModifiedVariable(
    const std::string& variableName) {
  return modifies_storage_.getStatementNumbersForVariable(variableName);
}

void UsesModifiesStorage::setVariableUsage(const std::string& variableName,
                                           int statementNumber) {
  uses_storage_.setVariableUsage(variableName, statementNumber);
}

std::set<std::string> UsesModifiesStorage::getUsedVariablesForStatement(
    int statementNumber) {
  return uses_storage_.getVariablesForStatement(statementNumber);
}

std::set<int> UsesModifiesStorage::getStatementNumbersForUsedVariable(
    const std::string& variableName) {
  return uses_storage_.getStatementNumbersForVariable(variableName);
}
