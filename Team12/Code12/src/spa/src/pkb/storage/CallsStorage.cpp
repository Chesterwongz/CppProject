#include "CallsStorage.h"

void CallsStorage::setCallsRelationship(const std::string& caller, const std::string& callee, int statementNumber) {
    callsMap[caller].emplace_back(std::make_pair(statementNumber, callee));
    calledByMap[callee].emplace_back(std::make_pair(statementNumber, caller));
}

void CallsStorage::setCallsStarRelationship(const std::string& caller, const std::string& callee, int statementNumber) {
    callsStarMap[caller].emplace_back(std::make_pair(statementNumber, callee));
    calledByStarMap[callee].emplace_back(std::make_pair(statementNumber, caller));
}

std::vector<std::pair<std::string, std::string>> CallsStorage::getCalls(const std::string& procedure) {
    std::vector<std::pair<std::string, std::string>> result;
    auto callsSet = callsMap[procedure];
    for (const auto& pair : callsSet) {
        result.push_back({ std::to_string(pair.first), pair.second });
    }
    return result;
}

std::vector<std::pair<std::string, std::string>> CallsStorage::getCallsStar(const std::string& procedure) {
    std::vector<std::pair<std::string, std::string>> result;
    auto callsStarSet = callsStarMap[procedure];
    for (const auto& pair : callsStarSet) {
        result.push_back({ std::to_string(pair.first), pair.second });
    }
    return result;
}

std::vector<std::pair<std::string, std::string>> CallsStorage::getCalledBy(const std::string& procedure) {
    std::vector<std::pair<std::string, std::string>> result;
    auto calledBySet = calledByMap[procedure];
    for (const auto& pair : calledBySet) {
        result.push_back({ std::to_string(pair.first), pair.second });
    }
    return result;
}

std::vector<std::pair<std::string, std::string>> CallsStorage::getCalledByStar(const std::string& procedure) {
    std::vector<std::pair<std::string, std::string>> result;
    auto calledByStarSet = calledByStarMap[procedure];
    for (const auto& pair : calledByStarSet) {
        result.push_back({ std::to_string(pair.first), pair.second });
    }
    return result;
}

std::string CallsStorage::getProcCalledOn(int stmtNum) {
    for (const auto& entry : callsMap) {
        for (const auto& pair : entry.second) {
            if (pair.first == stmtNum) {
                return pair.second;
            }
        }
    }
    return "";
}

std::vector<std::string> CallsStorage::getProcStarCalledOn(int stmtNum) {
    std::vector<std::string> result;
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

std::vector<std::pair<std::string, std::string>> CallsStorage::getCallingProcedures() {
    std::vector<std::pair<std::string, std::string>> result;
    for (const auto& entry : callsMap) {
        for (const auto& pair : entry.second) {
            result.push_back({ std::to_string(pair.first), entry.first });
        }
    }
    return result;
}

std::vector<std::pair<std::string, std::string>> CallsStorage::getCalledProcedures() {
    std::vector<std::pair<std::string, std::string>> result;
    for (const auto& entry : calledByMap) {
        for (const auto& pair : entry.second) {
            result.push_back({ std::to_string(pair.first), entry.first });
        }
    }
    return result;
}

bool CallsStorage::isCalls(const std::string& caller, const std::string& callee) {
    auto callsSet = callsMap[caller];
    for (const auto& pair : callsSet) {
        if (pair.second == callee) {
            return true;
        }
    }
    return false;
}

bool CallsStorage::isCallsStar(const std::string& caller, const std::string& callee) {
    auto callsStarSet = callsStarMap[caller];
    for (const auto& pair : callsStarSet) {
        if (pair.second == callee) {
            return true;
        }
    }
    return false;
}

bool CallsStorage::isCallingStmt(int stmtNum, const std::string& callee) {
    for (const auto& entry : callsMap) {
        for (const auto& pair : entry.second) {
            if (pair.first == stmtNum && pair.second == callee) {
                return true;
            }
        }
    }
    return false;
}

bool CallsStorage::isCallingStarStmt(int stmtNum, const std::string& callee) {
    for (const auto& entry : callsStarMap) {
        for (const auto& pair : entry.second) {
            if (pair.first == stmtNum && pair.second == callee) {
                return true;
            }
        }
    }
    return false;
}
