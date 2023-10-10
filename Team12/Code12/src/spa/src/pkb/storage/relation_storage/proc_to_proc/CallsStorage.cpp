#include "CallsStorage.h"

void CallsStorage::setCallsRelationship(const string& caller,
                                        const string& callee) {
  callsMap[caller].insert(callee);
  calledByMap[callee].insert(caller);
}

void CallsStorage::setCallsStarRelationship(const string& caller,
                                            const string& callee) {
  callsStarMap[caller].insert(callee);
  calledByStarMap[callee].insert(caller);
}

unordered_set<string> CallsStorage::getCalleeProcs(
    const string& procedure) const {
  if (callsMap.find(procedure) == callsMap.end()) {
    return {};
  }
  return callsMap.at(procedure);
}

unordered_set<string> CallsStorage::getCalleeProcsStar(
    const string& procedure) const {
  if (callsStarMap.find(procedure) == callsStarMap.end()) {
    return {};
  }
  return callsStarMap.at(procedure);
}

unordered_set<string> CallsStorage::getCallerProcs(
    const string& procedure) const {
  if (calledByMap.find(procedure) == calledByMap.end()) {
    return {};
  }
  return calledByMap.at(procedure);
}

unordered_set<string> CallsStorage::getCallerProcsStar(
    const string& procedure) const {
  unordered_set<string> result;
  if (calledByStarMap.find(procedure) == calledByStarMap.end()) {
    return {};
  }
  return calledByStarMap.at(procedure);
}

unordered_set<string> CallsStorage::getAllCallerProcs() {
  unordered_set<string> result;
  for (const auto& [caller, calleeSet] : callsMap) {
    result.insert(caller);
  }
  return result;
}

unordered_set<string> CallsStorage::getAllCalleeProcs() {
  unordered_set<string> result;
  for (const auto& [caller, calleeSet] : callsMap) {
    for (const auto& callee : calleeSet) {
      result.insert(callee);
    }
  }
  return result;
}

bool CallsStorage::isCalls(const string& caller, const string& callee) {
  auto& calleeSet = callsMap[caller];
  return std::any_of(
      calleeSet.begin(), calleeSet.end(),
      [&callee](const auto& currCallee) { return currCallee == callee; });
}

bool CallsStorage::isCallsStar(const string& caller, const string& callee) {
  auto& calleeSet = callsStarMap[caller];
  return std::any_of(
      calleeSet.begin(), calleeSet.end(),
      [&callee](const auto& currCallee) { return currCallee == callee; });
}

const unordered_map<string, unordered_set<string>>&
CallsStorage::getCallsStarMap() {
  return callsStarMap;
}

void CallsStorage::computeCallsStar() {
  for (const auto& [caller, calleeSet] : callsMap) {
    unordered_set<string> transitiveCallees =
        FunctionUtils<string, CallsStorage, const string&>::
            computeTransitiveRelationship(caller, &CallsStorage::getCalleeProcs,
                                          callsStarMap, this);
    for (const auto& callee : transitiveCallees) {
      setCallsStarRelationship(caller, callee);
    }
  }
}
