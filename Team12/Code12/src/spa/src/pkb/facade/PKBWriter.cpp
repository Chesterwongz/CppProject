#include "PKBWriter.h"

// ai-gen start(gpt-4, 2)
// void PKBWriter::processCallProcRelations(
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

template <typename ProcStoreType>
void PKBWriter::addRelationsForCallProcs(
    const string& callerProc, const unordered_set<string>& calleeProcs,
    const ProcStoreType& procStore,
    std::function<void(const string&, const string&)>& adder) {
  unordered_set<string> allVars;
  for (const auto& callee : calleeProcs) {
    vector<string> vars = procStore.getAllDirectSuccessorsOf(callee);
    allVars.insert(vars.begin(), vars.end());
  }
  for (const auto& var : allVars) {
    adder(var, callerProc);
  }
}

void PKBWriter::addUsesForCallsProc(const string& callerProc,
                                    const unordered_set<string>& calleeProcs) {
  const UsesPStore& usesPStore = store.getUsesProcStore();
  std::function<void(const string&, const string&)> addUsesFunc =
      [this](const string& var, const string& proc) { addUses(var, proc); };
  addRelationsForCallProcs(callerProc, calleeProcs, usesPStore, addUsesFunc);
}

void PKBWriter::addModifiesForCallProcs(
    const string& callerProc, const unordered_set<string>& calleeProcs) {
  const ModifiesPStore& modifiesPStore = store.getModifiesProcStore();
  std::function<void(const string&, const string&)> addModifiesFunc =
      [this](const string& var, const string& proc) { addModifies(var, proc); };
  addRelationsForCallProcs(callerProc, calleeProcs, modifiesPStore,
                           addModifiesFunc);
}

// void PKBWriter::setUsesForCalls(const string& callerProc,
//                                 const unordered_set<string>& calleeProcs) {
//   const UsesPStore& usesPStore = store.getUsesProcStore();
//
//   processCallProcRelations(callerProc, calleeProcs,
//                            &UsesPStore::getDirectSuccessorsOf,
//                            &PKBWriter::addUses);
// }

// void PKBWriter::setModifiesForCalls(const string& callerProc,
//                                     const unordered_set<string>& calleeProcs)
//                                     {
//   processCallProcRelations(callerProc, calleeProcs,
//                            &PKBStorage::getVarsModifiedByProc,
//                            &PKBWriter::addModifies);
// }

// void PKBWriter::addUsesForCallsProc(const string& callerProc,
//                                     const unordered_set<string>& calleeProcs)
//                                     {
//   const UsesPStore& usesPStore = store.getUsesProcStore();
//   unordered_set<string> allVars;
//   for (const auto& callee : calleeProcs) {
//     vector<string> vars = usesPStore.getAllDirectSuccessorsOf(callee);
//     allVars.insert(vars.begin(), vars.end());
//   }
//   for (const auto& var : allVars) {
//     addUses(var, callerProc);
//   }
// }
//
// void PKBWriter::addModifiesForCallProcs(
//     const string& callerProc, const unordered_set<string>& calleeProcs) {
//   const ModifiesPStore& modifiesPStore = store.getModifiesProcStore();
//   unordered_set<string> allVars;
//   for (const auto& callee : calleeProcs) {
//     vector<string> vars = modifiesPStore.getAllDirectSuccessorsOf(callee);
//     allVars.insert(vars.begin(), vars.end());
//   }
//   for (const auto& var : allVars) {
//     addUses(var, callerProc);
//   }
// }
//  ai-gen end

// void PKBWriter::processCallStmtRelations(
//     int stmtNum, const string& callee,
//     const unordered_set<string>& indirectCallees,
//     unordered_set<string> (PKBStorage::*retrieveVars)(const string&),
//     void (PKBWriter::*setStmtRelationship)(const string&, int)) {
//   unordered_set<string> allVars = (storage.*retrieveVars)(callee);
//   for (const auto& proc : indirectCallees) {
//     unordered_set<string> vars = (storage.*retrieveVars)(proc);
//     allVars.insert(vars.begin(), vars.end());
//   }
//   for (const auto& var : allVars) {
//     (this->*setStmtRelationship)(var, stmtNum);
//     for (int p : storage.getAllParents(stmtNum)) {
//       (this->*setStmtRelationship)(var, p);
//     }
//   }
// }

template <typename ProcStoreType>
void PKBWriter::addRelationsForCallStmts(
    int stmtNum, const string& callee,
    const unordered_set<string>& indirectCallees,
    const ProcStoreType& procStore,
    std::function<void(const string&, int)>& adder) {
  vector<string> calleeVars = procStore.getAllDirectSuccessorsOf(callee);
  unordered_set<string> allVars {calleeVars.begin(), calleeVars.end()};
  for (const auto& proc : indirectCallees) {
    vector<string> vars = procStore.getAllDirectSuccessorsOf(proc);
    allVars.insert(vars.begin(), vars.end());
  }
  for (const auto& var : allVars) {
    adder(var, stmtNum);
    for (int p : storage.getAllParents(stmtNum)) {
      adder(var, p);
    }
  }
}

void PKBWriter::addUsesForCallStmts(
    int stmtNum, const string& callee,
    const unordered_set<string>& indirectCallees) {
  const UsesPStore& usesPStore = store.getUsesProcStore();
  std::function<void(const string&, int)> addUsesFunc =
      [this](const string& var, int stmtNum) { addUses(var, stmtNum); };
  addRelationsForCallStmts(stmtNum, callee, indirectCallees, usesPStore,
                           addUsesFunc);
}

void PKBWriter::addModifiesForCallStmts(
    int stmtNum, const string& callee,
    const unordered_set<string>& indirectCallees) {
  const ModifiesPStore& modifiesPStore = store.getModifiesProcStore();
  std::function<void(const string&, int)> addModifiesFunc =
      [this](const string& var, int stmtNum) { addModifies(var, stmtNum); };
  addRelationsForCallStmts(stmtNum, callee, indirectCallees, modifiesPStore,
                           addModifiesFunc);
}

void PKBWriter::setIndirectCallsRelationship() {
  storage.computeCallsStar();
  for (const auto& [caller, callees] : storage.getCallsStarMap()) {
    addUsesForCallsProc(caller, callees);
    addModifiesForCallProcs(caller, callees);
  }

  for (const auto& [s, callee] : storage.getStmtCalleeMap()) {
    unordered_set<string> indirectCallees = storage.getCalleeProcsStar(callee);
    addUsesForCallStmts(s, callee, indirectCallees);
    addModifiesForCallStmts(s, callee, indirectCallees);
//    processCallStmtRelations(s, callee, indirectCallees,
//                             &PKBStorage::getVarsUsedByProc,
//                             &PKBWriter::addUses);
//    processCallStmtRelations(s, callee, indirectCallees,
//                             &PKBStorage::getVarsModifiedByProc,
//                             &PKBWriter::addModifies);
  }
}

void PKBWriter::setCFG(const std::string& procName, unique_ptr<CFG> cfg) {
  storage.addCfg(procName, std::move(cfg));
}
