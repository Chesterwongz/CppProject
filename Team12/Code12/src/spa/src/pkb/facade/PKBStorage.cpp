#include "PKBStorage.h"

PKBStorage::PKBStorage() = default;

void PKBStorage::setFollows(int stmtNum, int followingStatement) {
  followsStorage.setFollows(stmtNum, followingStatement);
}

void PKBStorage::setVariableModification(const string& varName, int stmtNum) {
  modifiesStorage.setVariableModification(varName, stmtNum);
}

void PKBStorage::setVariableModification(const string& varName,
                                         const string& procName) {
  modifiesStorage.setVariableModification(varName, procName);
}

void PKBStorage::setParent(int stmtNum, int childStatement) {
  parentStorage.setParent(stmtNum, childStatement);
}

void PKBStorage::setParentStar(int stmtNum, int childStatement) {
  parentStorage.setParentStar(stmtNum, childStatement);
}

void PKBStorage::setVariableUsage(const string& varName, int stmtNum) {
  usesStorage.setVariableUsage(varName, stmtNum);
}

void PKBStorage::setVariableUsage(const string& varName,
                                  const string& procName) {
  usesStorage.setVariableUsage(varName, procName);
}

void PKBStorage::setStatement(int stmtNum, StmtType stmtType) {
  statementStorage.setStatement(stmtNum, stmtType);
}

void PKBStorage::setVariable(const string& varName) {
  designEntitiesStorage.setVariable(varName);
}

void PKBStorage::setConstant(const string& constantValue) {
  designEntitiesStorage.setConstant(constantValue);
}

void PKBStorage::setProcedure(const string& procedureName, int startStatement) {
  designEntitiesStorage.setProcedure(procedureName, startStatement);
}

void PKBStorage::setAssignPattern(string varName, string rpn, int stmtNum) {
  patternStorage.setAssignPattern(varName, rpn, stmtNum);
}

void PKBStorage::setCallsRelationship(const string& callerProc,
                                      const string& calleeProc, int stmtNum) {
  callsStorage.setCallsRelationship(callerProc, calleeProc, stmtNum);
}

void PKBStorage::setCallsStarRelationship(const string& callerProc,
                                          const string& calleeProc,
                                          int stmtNum) {
  callsStorage.setCallsStarRelationship(callerProc, calleeProc, stmtNum);
}

std::set<string> PKBStorage::getAllVariables() {
  return designEntitiesStorage.getAllVariables();
}

std::set<string> PKBStorage::getAllConstants() {
  return designEntitiesStorage.getAllConstants();
}

std::set<string> PKBStorage::getAllProcedures() {
  return designEntitiesStorage.getAllProcedures();
}

std::set<int> PKBStorage::getStatementNumbersFromStatementType(
    StmtType stmtType) {
  return statementStorage.getStatementNumbersFromStatementType(stmtType);
}

StmtType PKBStorage::getStatementTypeFromStatementNumber(int stmtNum) {
  return statementStorage.getStatementTypeFromStatementNumber(stmtNum);
}

bool PKBStorage::isStatementType(int stmtNum, StmtType stmtType) {
  if (stmtNum < 0 || stmtType == StmtType::INVALID) {
    return false;
  }
  return statementStorage.isStatementType(stmtNum, stmtType);
}

int PKBStorage::getImmediateFollows(int stmtNum) {
  return followsStorage.getImmediateFollows(stmtNum);
}

int PKBStorage::getImmediateFollowedBy(int stmtNum) {
  return followsStorage.getImmediateFollowedBy(stmtNum);
}

std::set<int> PKBStorage::getAllFollows(int stmtNum) {
  return followsStorage.getAllFollows(stmtNum);
}

std::set<int> PKBStorage::getAllFollowedBy(int stmtNum) {
  return followsStorage.getAllFollowedBy(stmtNum);
}

std::set<int> PKBStorage::getImmediateChildren(int stmtNum) {
  return parentStorage.getImmediateChildren(stmtNum);
}

int PKBStorage::getImmediateParent(int stmtNum) {
  return parentStorage.getImmediateParent(stmtNum);
}

std::set<int> PKBStorage::getAllChildren(int stmtNum) {
  return parentStorage.getAllChildren(stmtNum);
}

std::set<int> PKBStorage::getAllParents(int stmtNum) {
  return parentStorage.getAllParents(stmtNum);
}

std::set<string> PKBStorage::getModifiedVariablesForStatement(int stmtNum) {
  return modifiesStorage.getVariablesForStatement(stmtNum);
}

unordered_set<string> PKBStorage::getModifiedVariablesForProc(
    const string& procName) {
  return modifiesStorage.getVariablesForProc(procName);
}

std::set<string> PKBStorage::getUsedVariablesForStatement(int stmtNum) {
  return usesStorage.getVariablesForStatement(stmtNum);
}

unordered_set<string> PKBStorage::getUsedVariablesForProc(
    const string& procName) {
  return usesStorage.getVariablesForProc(procName);
}

set<int> PKBStorage::getStatementNumbersForModifiedVariable(string varName) {
  return modifiesStorage.getStatementNumbersForVariable(varName);
}

set<int> PKBStorage::getStatementNumbersForUsedVariable(string varName) {
  return usesStorage.getStatementNumbersForVariable(varName);
}

vector<string> PKBStorage::getExactAssignPattern(string varName, string rpn,
                                                 bool isSynonym) {
  return patternStorage.getExactAssignPattern(varName, rpn, isSynonym);
}

vector<string> PKBStorage::getPartialAssignPattern(string varName, string rpn,
                                                   bool isSynonym) {
  return patternStorage.getPartialAssignPattern(varName, rpn, isSynonym);
}

vector<pair<string, string>> PKBStorage::getCalledBy(const string& procName) {
  return callsStorage.getCalledBy(procName);
}

vector<pair<string, string>> PKBStorage::getCalledStarBy(
    const string& procName) {
  return callsStorage.getCalledByStar(procName);
}

vector<pair<string, string>> PKBStorage::getProcsThatCall(
    const string& procName) {
  return callsStorage.getCalls(procName);
}

vector<pair<string, string>> PKBStorage::getProcsThatCallStar(
    const string& procName) {
  return callsStorage.getCallsStar(procName);
}

string PKBStorage::getProcCalledOn(int stmtNum) {
  return callsStorage.getProcCalledOn(stmtNum);
}

vector<string> PKBStorage::getProcStarCalledOn(int stmtNum) {
  return callsStorage.getProcStarCalledOn(stmtNum);
}

vector<pair<string, string>> PKBStorage::getCallingProcedures() {
  return callsStorage.getCallingProcedures();
}

vector<pair<string, string>> PKBStorage::getCalledProcedures() {
  return callsStorage.getCalledProcedures();
}

bool PKBStorage::isCalling(const string& caller, const string& callee) {
  return callsStorage.isCalls(caller, callee);
}

bool PKBStorage::isCallingStar(const string& caller, const string& callee) {
  return callsStorage.isCallsStar(caller, callee);
}

bool PKBStorage::isCallingStmt(int stmtNum, const string& callee) {
  return callsStorage.isCallingStmt(stmtNum, callee);
}

bool PKBStorage::isCallingStarStmt(int stmtNum, const string& callee) {
  return callsStorage.isCallingStarStmt(stmtNum, callee);
}

const unordered_map<string, vector<pair<int, string>>>&
PKBStorage::getCallsMap() {
  return callsStorage.getCallsMap();
}
