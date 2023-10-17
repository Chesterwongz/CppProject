#include "PKBWriter.h"

// ai-gen start(gpt-4, 2)
//void PKBWriter::processCallProcRelations(
//    const string& caller, const unordered_set<string>& callees,
//    unordered_set<string> (UsesPStore::*retrieveVars)(const string&),
//    void (PKBWriter::*setProcRelationship)(const string&, const string&)) {
//  unordered_set<string> allVars;
//  for (const auto& callee : callees) {
//    unordered_set<string> vars = (storage.*retrieveVars)(callee);
//    allVars.insert(vars.begin(), vars.end());
//  }
//  for (const auto& var : allVars) {
//    (this->*setProcRelationship)(var, caller);
//  }
//}

void PKBWriter::setUsesForCalls(const string& callerProc,
                                const unordered_set<string>& calleeProcs) {
  unordered_set<string> allVars;
  for (const auto& callee : calleeProcs) {
    const UsesPStore& usesPStore = store.getUsesProcStore();
    vector<string> vars = usesPStore.getAllDirectSuccessorsOf(callee);
    allVars.insert(vars.begin(), vars.end());
  }
  for (const auto& var : allVars) {
    addUses(var, callerProc);
  }
}

// void PKBWriter::setUsesForCalls(const string& callerProc,
//                                 const unordered_set<string>& calleeProcs) {
//   const UsesPStore& usesPStore = store.getUsesProcStore();
//
//   processCallProcRelations(callerProc, calleeProcs,
//                            &UsesPStore::getDirectSuccessorsOf,
//                            &PKBWriter::addUses);
// }

//void PKBWriter::setModifiesForCalls(const string& callerProc,
//                                    const unordered_set<string>& calleeProcs) {
//  processCallProcRelations(callerProc, calleeProcs,
//                           &PKBStorage::getVarsModifiedByProc,
//                           &PKBWriter::addModifies);
//}

void PKBWriter::setModifiesForCalls(const string& callerProc,
                                const unordered_set<string>& calleeProcs) {
  unordered_set<string> allVars;
  for (const auto& callee : calleeProcs) {
    const ModifiesPStore& modifiesPStore = store.getModifiesProcStore();
    vector<string> vars = modifiesPStore.getAllDirectSuccessorsOf(callee);
    allVars.insert(vars.begin(), vars.end());
  }
  for (const auto& var : allVars) {
    addUses(var, callerProc);
  }
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
                             &PKBWriter::addUses);
    processCallStmtRelations(s, callee, indirectCallees,
                             &PKBStorage::getVarsModifiedByProc,
                             &PKBWriter::addModifies);
  }
}

void PKBWriter::setCFG(const std::string& procName, unique_ptr<CFG> cfg) {
  storage.addCfg(procName, std::move(cfg));
}
