#include "PKBWriter.h"

void PKBWriter::setFollowsRelationship(int statementNumber,
                                       int followingStatement) {
  storage.setFollows(statementNumber, followingStatement);
}

void PKBWriter::setModifiesRelationship(const std::string& variableName,
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

void PKBWriter::setUsesRelationship(const std::string& variableName,
                                    int statementNumber) {
  storage.addUses(variableName, statementNumber);
}

void PKBWriter::setStatement(int statementNumber, StmtType statementType) {
  storage.setStatement(statementNumber, statementType);
}

void PKBWriter::setVariable(const std::string& variableName) {
  storage.setVariable(variableName);
}

void PKBWriter::setConstant(const std::string& constantValue) {
  storage.setConstant(constantValue);
}

void PKBWriter::setProcForStmt(const std::string& procedureName, int stmtNum) {
  storage.setProcForStmt(procedureName, stmtNum);
}

void PKBWriter::setAssignPattern(const std::string& variableName,
                                 const std::string& rpn, int statementNumber) {
  storage.setAssignPattern(variableName, rpn, statementNumber);
}

void PKBWriter::setWhilePattern(int statementNumber,
                                const std::string& variableName) {
  storage.setWhilePattern(statementNumber, variableName);
}

void PKBWriter::setIfPattern(int statementNumber,
                             const std::string& variableName) {
  storage.setIfPattern(statementNumber, variableName);
}

void PKBWriter::setUsesRelationship(const string& variableName,
                                    const string& procName) {
  storage.addUses(variableName, procName);
}

void PKBWriter::setModifiesRelationship(const string& variableName,
                                        const string& procName) {
  storage.addModifies(variableName, procName);
}

// ai-gen start(gpt-4, 2)
void PKBWriter::processCallProcRelations(
    const string& caller, const unordered_set<string>& callees,
    unordered_set<string> (PKBStorage::*retrieveVars)(const string&),
    void (PKBWriter::*setProcRelationship)(const string&, const string&)) {
  unordered_set<string> allVars;
  for (const auto& callee : callees) {
    unordered_set<string> vars = (storage.*retrieveVars)(callee);
    allVars.insert(vars.begin(), vars.end());
  }
  for (const auto& var : allVars) {
    (this->*setProcRelationship)(var, caller);
  }
}

void PKBWriter::setUsesForCalls(const string& callerProc,
                                const unordered_set<string>& calleeProcs) {
  processCallProcRelations(callerProc, calleeProcs,
                           &PKBStorage::getVarsUsedByProc,
                           &PKBWriter::setUsesRelationship);
}

void PKBWriter::setModifiesForCalls(const string& callerProc,
                                    const unordered_set<string>& calleeProcs) {
  processCallProcRelations(callerProc, calleeProcs,
                           &PKBStorage::getVarsModifiedByProc,
                           &PKBWriter::setModifiesRelationship);
}
// ai-gen end

void PKBWriter::processCallStmtRelations(
    int stmtNum, const string& callee,
    const unordered_set<string>& indirectCallees,
    unordered_set<string> (PKBStorage::*retrieveVars)(const string&),
    void (PKBWriter::*setStmtRelationship)(const string&, int)) {
  unordered_set<string> allVars = (storage.*retrieveVars)(callee);
  for (const auto& proc : indirectCallees) {
    unordered_set<string> vars = (storage.*retrieveVars)(proc);
    allVars.insert(vars.begin(), vars.end());
  }
  for (const auto& var : allVars) {
    (this->*setStmtRelationship)(var, stmtNum);
    for (int p : storage.getAllParents(stmtNum)) {
      (this->*setStmtRelationship)(var, p);
    }
  }
}

void PKBWriter::setIndirectCallsRelationship() {
  storage.computeCallsStar();
  for (const auto& [caller, callees] : storage.getCallsStarMap()) {
    setUsesForCalls(caller, callees);
    setModifiesForCalls(caller, callees);
  }

  for (const auto& [s, callee] : storage.getStmtCalleeMap()) {
    unordered_set<string> indirectCallees = storage.getCalleeProcsStar(callee);
    processCallStmtRelations(s, callee, indirectCallees,
                             &PKBStorage::getVarsUsedByProc,
                             &PKBWriter::setUsesRelationship);
    processCallStmtRelations(s, callee, indirectCallees,
                             &PKBStorage::getVarsModifiedByProc,
                             &PKBWriter::setModifiesRelationship);
    //    unordered_set<string> allUsedVars = storage.getVarsUsedByProc(callee);
    //    unordered_set<string> allModifiedVars =
    //        storage.getVarsModifiedByProc(callee);
    //    for (const auto &indirectCallee : indirectCallees) {
    //      unordered_set<string> usedVars =
    //          storage.getVarsUsedByProc(indirectCallee);
    //      unordered_set<string> modifiedVars =
    //          storage.getVarsModifiedByProc(indirectCallee);
    //      allUsedVars.insert(usedVars.begin(), usedVars.end());
    //      allModifiedVars.insert(modifiedVars.begin(), modifiedVars.end());
    //    }
    //    for (const auto &var : allUsedVars) {
    //      storage.addUses(var, s);
    //      for (int p : storage.getAllParents(s)) {
    //        storage.addUses(var, p);
    //      }
    //    }
    //    for (const auto &var : allModifiedVars) {
    //      storage.addModifies(var, s);
    //      for (int p : storage.getAllParents(s)) {
    //        storage.addModifies(var, p);
    //      }
    //    }
  }
}

void PKBWriter::setCallsRelationship(const string& callerProc,
                                     const string& calleeProc, int stmtNum) {
  storage.setCallsRelationship(callerProc, calleeProc, stmtNum);
}

void PKBWriter::setCallsStarRelationship(const string& callerProc,
                                         const string& calleeProc) {
  storage.setCallsStarRelationship(callerProc, calleeProc);
}

void PKBWriter::setCFG(const std::string& procName, unique_ptr<CFG> cfg) {
  storage.addCfg(procName, std::move(cfg));
}

void PKBWriter::addNext(int from, int to) { storage.addNext(from, to); }
