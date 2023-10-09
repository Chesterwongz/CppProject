#include "PKBStorage.h"

PKBStorage::PKBStorage() {}

void PKBStorage::setFollows(int statementNumber, int followingStatement) {
  followsStorage.setFollows(statementNumber, followingStatement);
}

void PKBStorage::setVariableModification(const std::string& variableName,
                                         int statementNumber) {
  modifiesStorage.setVariableModification(variableName, statementNumber);
}

void PKBStorage::setVariableModification(const std::string& variableName,
                                         const std::string& procName) {
  modifiesStorage.setVariableModification(variableName, procName);
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

void PKBStorage::setVariableUsage(const std::string& variableName,
                                  const std::string& procName) {
  usesStorage.setVariableUsage(variableName, procName);
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

void PKBStorage::setCallsRelationship(const std::string& callerProc,
                                      const std::string& calleeProc) {
  callsStorage.setCallsRelationship(callerProc, calleeProc);
}

void PKBStorage::setCallsStarRelationship(const std::string& callerProc,
                                          const std::string& calleeProc) {
  callsStorage.setCallsStarRelationship(callerProc, calleeProc);
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

unordered_set<string> PKBStorage::getModifiedVariablesForProc(
    const std::string& procName) {
  return modifiesStorage.getVariablesForProc(procName);
}

std::set<std::string> PKBStorage::getUsedVariablesForStatement(
    int statementNumber) {
  return usesStorage.getVariablesForStatement(statementNumber);
}

unordered_set<string> PKBStorage::getUsedVariablesForProc(
    const std::string& procName) {
  return usesStorage.getVariablesForProc(procName);
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

unordered_set<string> PKBStorage::getCallerProcs(const std::string& callee) {
  return callsStorage.getCallerProcs(callee);
}

unordered_set<string> PKBStorage::getCallerProcsStar(
    const std::string& callee) {
  return callsStorage.getCallerProcsStar(callee);
}

unordered_set<string> PKBStorage::getCalleeProcs(const std::string& caller) {
  return callsStorage.getCalleeProcs(caller);
}

unordered_set<string> PKBStorage::getCalleeProcsStar(
    const std::string& caller) {
  return callsStorage.getCalleeProcsStar(caller);
}

unordered_set<string> PKBStorage::getAllCallerProcs() {
  return callsStorage.getAllCallerProcs();
}

unordered_set<string> PKBStorage::getAllCalleeProcs() {
  return callsStorage.getAllCalleeProcs();
}

bool PKBStorage::isCalling(const std::string& caller,
                           const std::string& callee) {
  return callsStorage.isCalls(caller, callee);
}

bool PKBStorage::isCallingStar(const std::string& caller,
                               const std::string& callee) {
  return callsStorage.isCallsStar(caller, callee);
}

const unordered_map<string, unordered_set<string>>&
PKBStorage::getCalleeProcsMap() {
  return callsStorage.getCalleeProcsMap();
}
