#include "CallsStorage.h"

void CallsStorage::setCalls(const string &callerProc,
                            const string &calleeProc) {
  callsMap[callerProc].insert(calleeProc);
  calledByMap[calleeProc].insert(callerProc);
}

void CallsStorage::setCallsStar(const string &callerProc,
                                const string &calleeProc) {
  callsStarMap[callerProc].insert(calleeProc);
  calledByStarMap[calleeProc].insert(callerProc);
}

const std::unordered_map<string, std::unordered_set<string>>
    &CallsStorage::getCallsMap() {
  return callsMap;
}

std::unordered_set<string> CallsStorage::getDirectProcsCalledBy(
    const string &callerProc) {
  if (callsMap.find(callerProc) == callsMap.end()) {
    return {};
  }
  return callsMap[callerProc];
}

std::unordered_set<string> CallsStorage::getAllProcsCalledBy(
    const string &callerProc) {
  if (callsStarMap.find(callerProc) == callsStarMap.end()) {
    return {};
  }
  return callsStarMap[callerProc];
}
