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
    int stmtNum, const ProcStoreType& procStore,
    std::function<void(const string&, int)>& adder) {
  const CallsSStore& callsSStore = store.getCallsStmtStore();
  const CallsStore& callsPStore = store.getCallsStore();
  const ParentStore& parentStore = store.getParentStore();

  unordered_set<string> allCallees;
  unordered_set<string> allVars;

  for (const auto& callee : callsSStore.getAllDirectSuccessorsOf(stmtNum)) {
    vector<string> indirectCallees = callsPStore.getAllSuccessorsTOf(callee);
    allCallees.insert(indirectCallees.begin(), indirectCallees.end());

    vector<string> vars = procStore.getAllDirectSuccessorsOf(callee);
    allVars.insert(vars.begin(), vars.end());
  }

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

void PKBWriter::addUsesForCallStmts(int stmtNum) {
  const UsesPStore& usesPStore = store.getUsesProcStore();
  std::function<void(const string&, int)> addUsesFunc =
      [this](const string& var, int stmtNum) { addUses(var, stmtNum); };
  addRelationsForCallStmts(stmtNum, usesPStore, addUsesFunc);
}

void PKBWriter::addModifiesForCallStmts(int stmtNum) {
  const ModifiesPStore& modifiesPStore = store.getModifiesProcStore();
  std::function<void(const string&, int)> addModifiesFunc =
      [this](const string& var, int stmtNum) { addModifies(var, stmtNum); };
  addRelationsForCallStmts(stmtNum, modifiesPStore, addModifiesFunc);
}

void PKBWriter::setIndirectCallsRelationship() {
  const CallsStore& callsPStore = store.getCallsStore();
  const StmtStore& stmtStore = store.getStmtStore();
  for (const auto& [caller, callees] : callsPStore.getCallsPMap()) {
    addUsesForCallsProc(caller, callees);
    addModifiesForCallProcs(caller, callees);
  }

  if (!stmtStore.hasStmtType(StmtType::CALL)) {
    return;
  }

  for (const auto& s : stmtStore.getAllStmtsOf(StmtType::CALL)) {
    addUsesForCallStmts(s);
    addModifiesForCallStmts(s);
  }
}

void PKBWriter::setCFG(const std::string& procName, unique_ptr<CFG> cfg) {
  storage.addCfg(procName, std::move(cfg));
}
