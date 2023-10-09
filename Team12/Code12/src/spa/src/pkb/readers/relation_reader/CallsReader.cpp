#include "CallsReader.h"

unordered_set<string> CallsReader::getCallerProcs(const std::string& procName) {
  return callsStorage.getCallerProcs(procName);
}

unordered_set<string> CallsReader::getCallerProcsStar(
    const std::string& procName) {
  return callsStorage.getCallerProcsStar(procName);
}

unordered_set<string> CallsReader::getCalleeProcs(const std::string& procName) {
  return callsStorage.getCalleeProcs(procName);
}

unordered_set<string> CallsReader::getCalleeProcsStar(
    const std::string& procName) {
  return callsStorage.getCalleeProcsStar(procName);
}

unordered_set<string> CallsReader::getAllCallerProcs() {
  return callsStorage.getAllCallerProcs();
}

unordered_set<string> CallsReader::getAllCalleeProcs() {
  return callsStorage.getAllCalleeProcs();
}

bool CallsReader::isCalling(const std::string& caller,
                            const std::string& callee) {
  return callsStorage.isCalls(caller, callee);
}

bool CallsReader::isCallingStar(const std::string& caller,
                                const std::string& callee) {
  return callsStorage.isCalls(caller, callee);
}
