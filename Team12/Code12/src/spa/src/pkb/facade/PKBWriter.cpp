#include "PKBWriter.h"

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

template <typename ProcStoreType>
void PKBWriter::addRelationsForCallStmts(
    int stmtNum, const unordered_set<string>& allCallees,
    const ProcStoreType& procStore,
    std::function<void(const string&, int)>& adder) {
  const ParentStore& parentStore = store.getParentStore();
  unordered_set<string> allVars;
  for (const auto& proc : allCallees) {
    vector<string> vars = procStore.getAllDirectSuccessorsOf(proc);
    allVars.insert(vars.begin(), vars.end());
  }

  for (const auto& var : allVars) {
    adder(var, stmtNum);
    for (int p : parentStore.getAllAncestorsTOf(stmtNum)) {
      adder(var, p);
    }
  }
}

void PKBWriter::addUsesForCallStmts(int stmtNum,
                                    const unordered_set<string>& allCallees) {
  const UsesPStore& usesPStore = store.getUsesProcStore();
  std::function<void(const string&, int)> addUsesFunc =
      [this](const string& var, int stmtNum) { addUses(var, stmtNum); };
  addRelationsForCallStmts(stmtNum, allCallees, usesPStore, addUsesFunc);
}

void PKBWriter::addModifiesForCallStmts(
    int stmtNum, const unordered_set<string>& allCallees) {
  const ModifiesPStore& modifiesPStore = store.getModifiesProcStore();
  std::function<void(const string&, int)> addModifiesFunc =
      [this](const string& var, int stmtNum) { addModifies(var, stmtNum); };
  addRelationsForCallStmts(stmtNum, allCallees, modifiesPStore,
                           addModifiesFunc);
}

void PKBWriter::setIndirectCallsProcRelationships() {
  const CallsStore& callsPStore = store.getCallsStore();
  for (const auto& [caller, callees] : callsPStore.getCallsPMap()) {
    addUsesForCallsProc(caller, callees);
    addModifiesForCallProcs(caller, callees);
  }
}

void PKBWriter::setIndirectCallsStmtRelationships() {
  const CallsSStore& callsSStore = store.getCallsStmtStore();
  const CallsStore& callsPStore = store.getCallsStore();
  unordered_set<string> allCallees;
  for (const auto& [s, directCallees] : callsSStore.getCallsSMap()) {
    allCallees.insert(directCallees.begin(), directCallees.end());
    for (const auto& callee : directCallees) {
      vector<string> indirectCallees = callsPStore.getAllSuccessorsTOf(callee);
      allCallees.insert(indirectCallees.begin(), indirectCallees.end());
    }

    addUsesForCallStmts(s, allCallees);
    addModifiesForCallStmts(s, allCallees);
    allCallees.clear();
  }
}

void PKBWriter::setIndirectCallsRelationship() {
  setIndirectCallsProcRelationships();
  setIndirectCallsStmtRelationships();
}

void PKBWriter::setCFG(const std::string& procName, unique_ptr<CFG> cfg) {
  storage.addCfg(procName, std::move(cfg));
}
