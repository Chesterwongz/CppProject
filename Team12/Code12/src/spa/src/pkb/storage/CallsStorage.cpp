#include "CallsStorage.h"

void CallsStorage::setCalls(const std::string &callerProc,
                            const std::string &calleeProc) {
    callsMap[callerProc].insert(calleeProc);
    calledByMap[calleeProc].insert(callerProc);
}

void CallsStorage::setCallsStar(const std::string &callerProc,
                                const std::string &calleeProc) {
    callsStarMap[callerProc].insert(calleeProc);
    calledByStarMap[calleeProc].insert(callerProc);
}

const std::unordered_map<std::string, std::unordered_set<std::string>>
&CallsStorage::getCallsMap() {
    return callsMap;
}

std::unordered_set<std::string> CallsStorage::getDirectProcsCalledBy(
    const std::string &callerProc) {
    if (callsMap.find(callerProc) == callsMap.end()) {
        return {};
    }
    return callsMap[callerProc];
}

std::unordered_set<std::string> CallsStorage::getAllProcsCalledBy(
    const std::string &callerProc) {
    if (callsStarMap.find(callerProc) == callsStarMap.end()) {
        return {};
    }
    return callsStarMap[callerProc];
}
