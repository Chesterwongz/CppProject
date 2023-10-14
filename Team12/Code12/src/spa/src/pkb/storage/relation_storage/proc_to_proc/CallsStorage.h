#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/interfaces/storage/relation_storage/ICallsStorage.h"
#include "pkb/utils/FunctionUtils.h"

using std::unordered_set, std::unordered_map, std::string, std::vector,
    std::pair, std::make_pair;

class CallsStorage : public ICallsStorage {
 public:
  void setCallsRelationship(const string& caller, const string& callee,
                            int stmtNum) override;
  void setCallsStarRelationship(const string& caller,
                                const string& callee) override;

  // return calleeNames that are directly called by caller
  unordered_set<string> getCalleeProcs(const string& caller) override;

  // return calleeNames that are directly or indirectly called by caller
  unordered_set<string> getCalleeProcsStar(const string& caller) override;

  // return callerNames that directly call callee
  unordered_set<string> getCallerProcs(const string& callee) override;

  // return callerNames that indirectly call callee
  unordered_set<string> getCallerProcsStar(const string& callee) override;

  bool isCalls(const string& caller, const string& callee) override;
  bool isCallsStar(const string& caller, const string& callee) override;

  // return all callers
  unordered_set<string> getAllCallerProcs() override;

  // return all pairs (stmtNum, calleeName) that are called by another procedure
  unordered_set<string> getAllCalleeProcs() override;

  const unordered_map<string, unordered_set<string>>& getCallsStarMap();

  void computeCallsStar();

  const unordered_map<int, string>& getStmtCalleeMap();

 private:
  // callerProc -> calleeProc
  unordered_map<string, unordered_set<string>> callsMap;
  // callerProc -> calleeProc
  unordered_map<string, unordered_set<string>> callsStarMap;
  // calleeProc -> callerProc
  unordered_map<string, unordered_set<string>> calledByMap;
  // calleeProc -> callerProc
  unordered_map<string, unordered_set<string>> calledByStarMap;
  // call stmt -> direct calleeProc, for call.procName
  unordered_map<int, string> stmtCalleeMap;
  // direct calleeProc -> call stmt,
  // for computing uses and modifies for indirect calls
  unordered_map<string, unordered_set<int>> calleeStmtMap;
};
