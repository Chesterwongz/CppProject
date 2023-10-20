#include "PKBWriter.h"

template <typename ProcStoreType>
void PKBWriter::addRelationsForCallProcs(
    const string& callerProc, const unordered_set<string>& calleeProcs,
    const ProcStoreType& procStore,
    std::function<void(const string&, const string&)>& adder) {
  unordered_set<string> allVars;
  for (const auto& callee : calleeProcs) {
    if (!procStore.hasDirectSuccessor(callee)) continue;
    const auto& vars = procStore.getDirectSuccessors(callee);
    allVars.reserve(vars.size());
    allVars.insert(vars.begin(), vars.end());
  }
  for (const auto& var : allVars) {
    adder(var, callerProc);
  }
}

void PKBWriter::addUsesForCallsProc(const string& callerProc,
                                    const unordered_set<string>& calleeProcs) {
  std::function<void(const string&, const string&)> addUsesFunc =
      [this](const string& var, const string& proc) { addUses(var, proc); };
  addRelationsForCallProcs(callerProc, calleeProcs, usesPStore, addUsesFunc);
}

void PKBWriter::addModifiesForCallProcs(
    const string& callerProc, const unordered_set<string>& calleeProcs) {
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
  unordered_set<string> allVars;
  for (const auto& callee : allCallees) {
    if (!procStore.hasDirectSuccessor(callee)) continue;
    const auto& vars = procStore.getDirectSuccessors(callee);
    allVars.reserve(vars.size());
    allVars.insert(vars.begin(), vars.end());
  }

  for (const auto& var : allVars) {
    adder(var, stmtNum);
    if (parentStore.hasAncestorsT(stmtNum)) continue;
    for (const int& p : parentStore.getAncestorsT(stmtNum)) {
      adder(var, p);
    }
  }
}

void PKBWriter::addUsesForCallStmts(int stmtNum,
                                    const unordered_set<string>& allCallees) {
  std::function<void(const string&, int)> addUsesFunc =
      [this](const string& var, int stmtNum) { addUses(var, stmtNum); };
  addRelationsForCallStmts(stmtNum, allCallees, usesPStore, addUsesFunc);
}

void PKBWriter::addModifiesForCallStmts(
    int stmtNum, const unordered_set<string>& allCallees) {
  std::function<void(const string&, int)> addModifiesFunc =
      [this](const string& var, int stmtNum) { addModifies(var, stmtNum); };
  addRelationsForCallStmts(stmtNum, allCallees, modifiesPStore,
                           addModifiesFunc);
}

void PKBWriter::setIndirectCallsProcRelationships() {
  for (const auto& [caller, callees] : callsPStore.getRelationsT()) {
    addUsesForCallsProc(caller, callees);
    addModifiesForCallProcs(caller, callees);
  }
}

void PKBWriter::setIndirectCallsStmtRelationships() {
  unordered_set<string> allCallees;
  for (const auto& [s, directCallees] : callsSStore.getDirectRelations()) {
    allCallees.insert(directCallees.begin(), directCallees.end());
    for (const auto& callee : directCallees) {
      if (!callsPStore.hasSuccessorsT(callee)) continue;
      const auto& indirectCallees = callsPStore.getSuccessorsT(callee);
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
