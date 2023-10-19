#include "CallsReader.h"

std::vector<std::string> CallsReader::getCallerProcs(const std::string& proc2) {
  return callsStore.getAllDirectAncestorsOf(proc2);
}

std::vector<std::string> CallsReader::getCallerProcsStar(
    const std::string& proc2) {
  return callsStore.getAllAncestorsTOf(proc2);
}

std::vector<std::string> CallsReader::getCalleeProcs(const std::string& proc1) {
  return callsStore.getAllDirectSuccessorsOf(proc1);
}

std::vector<std::string> CallsReader::getCalleeProcsStar(
    const std::string& proc1) {
  return callsStore.getAllSuccessorsTOf(proc1);
}

std::vector<std::pair<std::string, std::string>> CallsReader::getCallPairs() {
  return callsStore.getAllDirectRelations();
}

std::vector<std::pair<std::string, std::string>>
CallsReader::getCallsStarPairs() {
  return callsStore.getAllRelationsT();
}

bool CallsReader::hasCalls(const std::string& proc1, const std::string& proc2) {
  return callsStore.hasDirectRelation(proc1, proc2);
}

bool CallsReader::hasCallsT(const std::string& proc1,
                            const std::string& proc2) {
  return callsStore.hasRelationT(proc1, proc2);
}
