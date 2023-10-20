#include "CallsReader.h"

std::vector<std::string> CallsReader::getCallerProcs(const std::string& proc2) {
  if (!callsStore.hasDirectAncestor(proc2)) {
    return {};
  }
  const auto& rawRes = callsStore.getDirectAncestors(proc2);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::string> CallsReader::getCallerProcsStar(
    const std::string& proc2) {
  const auto& rawRes = callsStore.getAncestorsT(proc2);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::string> CallsReader::getCalleeProcs(const std::string& proc1) {
  if (!callsStore.hasDirectSuccessor(proc1)) {
    return {};
  }
  const auto& rawRes = callsStore.getDirectSuccessors(proc1);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::string> CallsReader::getCalleeProcsStar(
    const std::string& proc1) {
  const auto& rawRes = callsStore.getSuccessorsT(proc1);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::pair<std::string, std::string>> CallsReader::getCallPairs() {
  const auto& rawRes = callsStore.getDirectRelations();
  return CollectionUtils::transformMapSetABToVectorAB<std::string, std::string>(
      rawRes);
}

std::vector<std::pair<std::string, std::string>>
CallsReader::getCallsStarPairs() {
  return CollectionUtils::transformMapSetABToVectorAB(
      callsStore.getRelationsT());
}

bool CallsReader::hasCalls(const std::string& proc1, const std::string& proc2) {
  return callsStore.hasDirectRelation(proc1, proc2);
}

bool CallsReader::hasCallsT(const std::string& proc1,
                            const std::string& proc2) {
  return callsStore.hasRelationT(proc1, proc2);
}
