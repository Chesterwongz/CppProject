#include "CallsStorage.h"

void CallsStorage::setCallsRelationship(const string& caller,
                                        const string& callee,
                                        int statementNumber) {
  callsMap[caller].emplace_back(make_pair(statementNumber, callee));
  calledByMap[callee].emplace_back(make_pair(statementNumber, caller));
}

void CallsStorage::setCallsStarRelationship(const string& caller,
                                            const string& callee,
                                            int statementNumber) {
  callsStarMap[caller].emplace_back(make_pair(statementNumber, callee));
  calledByStarMap[callee].emplace_back(make_pair(statementNumber, caller));
}

vector<pair<string, string>> CallsStorage::getCalleeProcs(const string& procedure) {
  vector<pair<string, string>> result;
  auto callsSet = callsMap[procedure];
  for (const auto& [stmtNum, callee] : callsSet) {
    result.emplace_back(std::to_string(stmtNum), callee);
  }
  return result;
}

vector<pair<string, string>> CallsStorage::getCalleeProcsStar(
    const string& procedure) {
  vector<pair<string, string>> result;
  auto callsStarSet = callsStarMap[procedure];
  for (const auto& [stmtNum, callee] : callsStarSet) {
    result.emplace_back(std::to_string(stmtNum), callee);
  }
  return result;
}

vector<pair<string, string>> CallsStorage::getCallerProcs(
    const string& procedure) {
  vector<pair<string, string>> result;
  if (calledByMap.find(procedure) == calledByMap.end()) {
    return result;
  }
  auto calledBySet = calledByMap[procedure];
  for (const auto& [stmtNum, caller] : calledBySet) {
    result.emplace_back(std::to_string(stmtNum), caller);
  }
  return result;
}

vector<pair<string, string>> CallsStorage::getCallerProcsStar(
    const string& procedure) {
  vector<pair<string, string>> result;
  if (calledByStarMap.find(procedure) == calledByStarMap.end()) {
    return result;
  }
  auto calledByStarSet = calledByStarMap[procedure];
  for (const auto& [stmtNum, caller] : calledByStarSet) {
    result.emplace_back(std::to_string(stmtNum), caller);
  }
  return result;
}

string CallsStorage::getProcCalledOn(int stmtNum) {
  for (const auto& [caller, stmtNumCalleeVector] : callsMap) {
    for (const auto& [callStmtNum, callee] : stmtNumCalleeVector) {
      if (callStmtNum == stmtNum) {
        return callee;
      }
    }
  }
  return "";
}

vector<string> CallsStorage::getProcStarCalledOn(int stmtNum) {
  vector<string> result;
  for (const auto& [caller, stmtNumCalleeVector] : callsStarMap) {
    for (const auto& [callStmtNum, callee] : stmtNumCalleeVector) {
      if (callStmtNum == stmtNum) {
        result.push_back(callee);
      }
    }
  }
  return result;
}

vector<pair<string, string>> CallsStorage::getCallingProcedures() {
  vector<pair<string, string>> result;
  for (const auto& [caller, stmtNumCalleeVector] : callsMap) {
    for (const auto& [callStmtNum, callee] : stmtNumCalleeVector) {
      result.emplace_back(std::to_string(callStmtNum), caller);
    }
  }
  return result;
}

vector<pair<string, string>> CallsStorage::getCalledProcedures() {
  vector<pair<string, string>> result;
  for (const auto& [callee, stmtNumCallerVector] : calledByMap) {
    for (const auto& [callStmtNum, caller] : stmtNumCallerVector) {
      result.emplace_back(std::to_string(callStmtNum), callee);
    }
  }
  return result;
}

bool CallsStorage::isCalls(const string& caller, const string& callee) {
  auto& callsSet = callsMap[caller];
  return std::any_of(
      callsSet.begin(), callsSet.end(),
      [&callee](const auto& pair) { return pair.second == callee; });
}

bool CallsStorage::isCallsStar(const string& caller, const string& callee) {
  auto& callsSet = callsStarMap[caller];
  return std::any_of(
      callsSet.begin(), callsSet.end(),
      [&callee](const auto& pair) { return pair.second == callee; });
}

bool CallsStorage::isCallingStmt(int stmtNum, const string& callee) {
  for (const auto& entry : callsMap) {
    for (const auto& pair : entry.second) {
      if (pair.first == stmtNum && pair.second == callee) {
        return true;
      }
    }
  }
  return false;
}

bool CallsStorage::isCallingStarStmt(int stmtNum, const string& callee) {
  for (const auto& entry : callsStarMap) {
    for (const auto& pair : entry.second) {
      if (pair.first == stmtNum && pair.second == callee) {
        return true;
      }
    }
  }
  return false;
}

const unordered_map<string, vector<pair<int, string>>>&
CallsStorage::getCalleeProcsMap() {
  return callsMap;
}
