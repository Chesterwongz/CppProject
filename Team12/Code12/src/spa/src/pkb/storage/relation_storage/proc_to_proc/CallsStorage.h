#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "pkb/utils/FunctionUtils.h"

using std::unordered_set, std::unordered_map, std::string, std::vector,
    std::pair, std::make_pair;

class CallsStorage {
 public:
  void setCallsRelationship(const string& caller, const string& callee);
  void setCallsStarRelationship(const string& caller, const string& callee);

  // return calleeNames that are directly called by caller
  [[nodiscard]] unordered_set<string> getCalleeProcs(
      const string& caller) const;

  // return calleeNames that are directly or indirectly called by caller
  [[nodiscard]] unordered_set<string> getCalleeProcsStar(
      const string& caller) const;

  // return callerNames that directly call callee
  [[nodiscard]] unordered_set<string> getCallerProcs(
      const string& callee) const;

  // return callerNames that indirectly call callee
  [[nodiscard]] unordered_set<string> getCallerProcsStar(
      const string& callee) const;

  bool isCalls(const string& caller, const string& callee);
  bool isCallsStar(const string& caller, const string& callee);

  // return all callers
  unordered_set<string> getAllCallerProcs();

  // return all pairs (stmtNum, calleeName) that are called by another procedure
  unordered_set<string> getAllCalleeProcs();

  const unordered_map<string, unordered_set<string>>& getCallsStarMap();

  void computeCallsStar();

 private:
  // callerProc -> calleeProc
  unordered_map<string, unordered_set<string>> callsMap;
  // callerProc -> calleeProc
  unordered_map<string, unordered_set<string>> callsStarMap;
  // calleeProc -> callerProc
  unordered_map<string, unordered_set<string>> calledByMap;
  // calleeProc -> callerProc
  unordered_map<string, unordered_set<string>> calledByStarMap;
};
