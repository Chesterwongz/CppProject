#include "PKBStorage.h"

PKBStorage::PKBStorage() {}

void PKBStorage::setFollows(int statementNumber, int followingStatement) {
  followsStorage.setFollows(statementNumber, followingStatement);
}

void PKBStorage::setVariableModification(const std::string& variableName,
                                         int statementNumber) {
  modifiesStorage.setVariableModification(variableName, statementNumber);
}

void PKBStorage::setParent(int statementNumber, int childStatement) {
  parentStorage.setParent(statementNumber, childStatement);
}

void PKBStorage::setParentStar(int statementNumber, int childStatement) {
  parentStorage.setParentStar(statementNumber, childStatement);
}

void PKBStorage::setVariableUsage(const std::string& variableName,
                                  int statementNumber) {
  usesStorage.setVariableUsage(variableName, statementNumber);
}

void PKBStorage::setStatement(int statementNumber, StmtType statementType) {
  statementStorage.setStatement(statementNumber, statementType);
}

void PKBStorage::setVariable(const std::string& variableName) {
  designEntitiesStorage.setVariable(variableName);
}

void PKBStorage::setConstant(const std::string& constantValue) {
  designEntitiesStorage.setConstant(constantValue);
}

void PKBStorage::setProcedure(const std::string& procedureName,
                              int startStatement) {
  designEntitiesStorage.setProcedure(procedureName, startStatement);
}

void PKBStorage::setAssignPattern(std::string variableName, std::string rpn,
                                  int statementNumber) {
  patternStorage.setAssignPattern(variableName, rpn, statementNumber);
}

std::set<std::string> PKBStorage::getAllVariables() {
  return designEntitiesStorage.getAllVariables();
}

std::set<std::string> PKBStorage::getAllConstants() {
  return designEntitiesStorage.getAllConstants();
}

std::set<std::string> PKBStorage::getAllProcedures() {
  return designEntitiesStorage.getAllProcedures();
}

std::set<int> PKBStorage::getStatementNumbersFromStatementType(
    StmtType statementType) {
  return statementStorage.getStatementNumbersFromStatementType(statementType);
}

StmtType PKBStorage::getStatementTypeFromStatementNumber(int statementNumber) {
  return statementStorage.getStatementTypeFromStatementNumber(statementNumber);
}

bool PKBStorage::isStatementType(int statementNumber, StmtType statementType) {
  if (statementNumber < 0 || statementType == StmtType::INVALID) {
    return false;
  }
  return statementStorage.isStatementType(statementNumber, statementType);
}

int PKBStorage::getImmediateFollows(int statementNumber) {
  return followsStorage.getImmediateFollows(statementNumber);
}

int PKBStorage::getImmediateFollowedBy(int statementNumber) {
  return followsStorage.getImmediateFollowedBy(statementNumber);
}

std::set<int> PKBStorage::getAllFollows(int statementNumber) {
  return followsStorage.getAllFollows(statementNumber);
}

std::set<int> PKBStorage::getAllFollowedBy(int statementNumber) {
  return followsStorage.getAllFollowedBy(statementNumber);
}

std::set<int> PKBStorage::getImmediateChildren(int statementNumber) {
  return parentStorage.getImmediateChildren(statementNumber);
}

int PKBStorage::getImmediateParent(int statementNumber) {
  return parentStorage.getImmediateParent(statementNumber);
}

std::set<int> PKBStorage::getAllChildren(int statementNumber) {
  return parentStorage.getAllChildren(statementNumber);
}

std::set<int> PKBStorage::getAllParents(int statementNumber) {
  return parentStorage.getAllParents(statementNumber);
}

std::set<std::string> PKBStorage::getModifiedVariablesForStatement(
    int statementNumber) {
  return modifiesStorage.getVariablesForStatement(statementNumber);
}

std::set<std::string> PKBStorage::getUsedVariablesForStatement(
    int statementNumber) {
  return usesStorage.getVariablesForStatement(statementNumber);
}

std::set<int> PKBStorage::getStatementNumbersForModifiedVariable(
    std::string variableName) {
  return modifiesStorage.getStatementNumbersForVariable(variableName);
}

std::set<int> PKBStorage::getStatementNumbersForUsedVariable(
    std::string variableName) {
  return usesStorage.getStatementNumbersForVariable(variableName);
}

std::vector<std::string> PKBStorage::getExactAssignPattern(
    std::string variableName, std::string rpn, bool isSynonym) {
  return patternStorage.getExactAssignPattern(variableName, rpn, isSynonym);
}

std::vector<std::string> PKBStorage::getPartialAssignPattern(
    std::string variableName, std::string rpn, bool isSynonym) {
  return patternStorage.getPartialAssignPattern(variableName, rpn, isSynonym);
}
