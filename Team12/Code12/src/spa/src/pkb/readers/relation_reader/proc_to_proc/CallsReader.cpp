#include "CallsReader.h"

std::vector<std::string> CallsReader::getCallerProcs(const std::string& proc2) {
  if (!callsStore.hasDirectAncestors(proc2)) {
    return {};
  }
  const auto& rawRes = callsStore.getDirectAncestors(proc2);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::string> CallsReader::getCallerProcsStar(
    const std::string& proc2) {
  if (!callsStore.hasAncestorsT(proc2)) {
    return {};
  }
  const auto& rawRes = callsStore.getAncestorsT(proc2);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::string> CallsReader::getCalleeProcs(const std::string& proc1) {
  if (!callsStore.hasDirectSuccessors(proc1)) {
    return {};
  }
  const auto& rawRes = callsStore.getDirectSuccessors(proc1);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::string> CallsReader::getCalleeProcsStar(
    const std::string& proc1) {
  if (!callsStore.hasSuccessorsT(proc1)) {
    return {};
  }
  const auto& rawRes = callsStore.getSuccessorsT(proc1);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::pair<std::string, std::string>> CallsReader::getCallPairs() {
  const auto& rawRes = callsStore.getDirectRelations();
  return CollectionUtils::mapSetToPairVector<std::string, std::string>(rawRes);
}

std::vector<std::pair<std::string, std::string>>
CallsReader::getCallsStarPairs() {
  return CollectionUtils::mapSetToPairVector(callsStore.getRelationsT());
}

bool CallsReader::hasCalls(const std::string& proc1, const std::string& proc2) {
  return callsStore.hasDirectRelation(proc1, proc2);
}

bool CallsReader::hasCallsT(const std::string& proc1,
                            const std::string& proc2) {
  return callsStore.hasRelationT(proc1, proc2);
}
