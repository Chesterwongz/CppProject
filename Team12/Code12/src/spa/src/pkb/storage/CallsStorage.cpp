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

vector<pair<string, string>> CallsStorage::getCalls(const string& procedure) {
  vector<pair<string, string>> result;
  auto callsSet = callsMap[procedure];
  for (const auto& pair : callsSet) {
    result.emplace_back(std::to_string(pair.first), pair.second);
  }
  return result;
}

vector<pair<string, string>> CallsStorage::getCallsStar(
    const string& procedure) {
  vector<pair<string, string>> result;
  auto callsStarSet = callsStarMap[procedure];
  for (const auto& pair : callsStarSet) {
    result.emplace_back(std::to_string(pair.first), pair.second);
  }
  return result;
}

vector<pair<string, string>> CallsStorage::getCalledBy(
    const string& procedure) {
  vector<pair<string, string>> result;
  auto calledBySet = calledByMap[procedure];
  for (const auto& pair : calledBySet) {
    result.emplace_back(std::to_string(pair.first), pair.second);
  }
  return result;
}

vector<pair<string, string>> CallsStorage::getCalledByStar(
    const string& procedure) {
  vector<pair<string, string>> result;
  auto calledByStarSet = calledByStarMap[procedure];
  for (const auto& pair : calledByStarSet) {
    result.emplace_back(std::to_string(pair.first), pair.second);
  }
  return result;
}

string CallsStorage::getProcCalledOn(int stmtNum) {
  for (const auto& entry : callsMap) {
    for (const auto& pair : entry.second) {
      if (pair.first == stmtNum) {
        return pair.second;
      }
    }
  }
  return "";
}

vector<string> CallsStorage::getProcStarCalledOn(int stmtNum) {
  vector<string> result;
  for (const auto& entry : callsStarMap) {
    for (const auto& pair : entry.second) {
      if (pair.first == stmtNum) {
        result.push_back(pair.second);
        break;
      }
    }
  }
  return result;
}

vector<pair<string, string>> CallsStorage::getCallingProcedures() {
  vector<pair<string, string>> result;
  for (const auto& entry : callsMap) {
    for (const auto& pair : entry.second) {
      result.emplace_back(std::to_string(pair.first), entry.first);
    }
  }
  return result;
}

vector<pair<string, string>> CallsStorage::getCalledProcedures() {
  vector<pair<string, string>> result;
  for (const auto& entry : calledByMap) {
    for (const auto& pair : entry.second) {
      result.emplace_back(std::to_string(pair.first), entry.first);
    }
  }
  return result;
}

bool CallsStorage::isCalls(const string& caller, const string& callee) {
  auto callsSet = callsMap[caller];
  for (const auto& pair : callsSet) {
    if (pair.second == callee) {
      return true;
    }
  }
  return false;
}

bool CallsStorage::isCallsStar(const string& caller, const string& callee) {
  auto callsStarSet = callsStarMap[caller];
  for (const auto& pair : callsStarSet) {
    if (pair.second == callee) {
      return true;
    }
  }
  return false;
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
