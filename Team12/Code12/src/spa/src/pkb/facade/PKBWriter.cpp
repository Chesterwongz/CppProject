#include "PKBWriter.h"

void PKBWriter::setFollowsRelationship(int statementNumber,
                                       int followingStatement) {
  storage.setFollows(statementNumber, followingStatement);
}

void PKBWriter::setModifiesRelationship(const std::string &variableName,
                                        int statementNumber) {
  storage.addModifies(variableName, statementNumber);
}

void PKBWriter::setParentRelationship(int statementNumber, int childStatement) {
  storage.setParent(statementNumber, childStatement);
}

void PKBWriter::setParentStarRelationship(int statementNumber,
                                          int childStatement) {
  storage.setParentStar(statementNumber, childStatement);
}

void PKBWriter::setUsesRelationship(const std::string &variableName,
                                    int statementNumber) {
  storage.addUses(variableName, statementNumber);
}

void PKBWriter::setStatement(int statementNumber, StmtType statementType) {
  storage.setStatement(statementNumber, statementType);
}

void PKBWriter::setVariable(const std::string &variableName) {
  storage.setVariable(variableName);
}

void PKBWriter::setConstant(const std::string &constantValue) {
  storage.setConstant(constantValue);
}

void PKBWriter::setProcForStmt(const std::string &procedureName, int stmtNum) {
  storage.setProcForStmt(procedureName, stmtNum);
}

void PKBWriter::setAssignPattern(const std::string &variableName,
                                 const std::string &rpn, int statementNumber) {
  storage.setAssignPattern(variableName, rpn, statementNumber);
}
void PKBWriter::setWhilePattern(int statementNumber,
                                const std::string &varName) {}

void PKBWriter::setIfPattern(int statementNumber, const std::string &varName) {}

void PKBWriter::setUsesRelationship(const string &variableName,
                                    const string &procName) {
  storage.addUses(variableName, procName);
}

void PKBWriter::setModifiesRelationship(const string &variableName,
                                        const string &procName) {
  storage.addModifies(variableName, procName);
}

void PKBWriter::processCallStmtRelations(
    void (PKBWriter::*setStmtRelationship)(const string &, int),
    const string &callee, const string &var) {
  unordered_set<int> stmts = storage.getCallStmtsFromCallee(callee);
  for (const auto &callStmt : stmts) {
    (this->*setStmtRelationship)(var, callStmt);
  }
}

// ai-gen start(gpt-4, 2)
void PKBWriter::processCallRelations(
    const string &caller, const unordered_set<string> &callees,
    unordered_set<string> (PKBStorage::*retrieveVars)(const string &),
    void (PKBWriter::*setProcRelationship)(const string &, const string &),
    void (PKBWriter::*setStmtRelationship)(const string &, int)) {
  for (const auto &callee : callees) {
    unordered_set<string> vars = (storage.*retrieveVars)(callee);
    for (const auto &var : vars) {
      (this->*setProcRelationship)(var, caller);
      processCallStmtRelations(setStmtRelationship, callee, var);
    }
  }
}

void PKBWriter::setUsesForCalls(const string &callerProc,
                                const unordered_set<string> &calleeProcs) {
  processCallRelations(callerProc, calleeProcs, &PKBStorage::getVarsUsedByProc,
                       &PKBWriter::setUsesRelationship,
                       &PKBWriter::setUsesRelationship);
}

void PKBWriter::setModifiesForCalls(const string &callerProc,
                                    const unordered_set<string> &calleeProcs) {
  processCallRelations(
      callerProc, calleeProcs, &PKBStorage::getVarsModifiedByProc,
      &PKBWriter::setModifiesRelationship, &PKBWriter::setModifiesRelationship);
}
// ai-gen end

void PKBWriter::setIndirectCallsRelationship() {
  storage.computeCallsStar();
  for (const auto &[caller, callees] : storage.getCallsStarMap()) {
    setUsesForCalls(caller, callees);
    setModifiesForCalls(caller, callees);
  }
}

void PKBWriter::setCallsRelationship(const string &callerProc,
                                     const string &calleeProc, int stmtNum) {
  storage.setCallsRelationship(callerProc, calleeProc, stmtNum);
}

void PKBWriter::setCallsStarRelationship(const string &callerProc,
                                         const string &calleeProc) {
  storage.setCallsStarRelationship(callerProc, calleeProc);
}

void PKBWriter::setCFG(const std::string &procName, unique_ptr<CFG> cfg) {
  storage.addCfg(procName, std::move(cfg));
}

void PKBWriter::addNext(int from, int to) { storage.addNext(from, to); }
