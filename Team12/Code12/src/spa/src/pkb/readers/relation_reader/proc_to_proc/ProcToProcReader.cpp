#include "ProcToProcReader.h"

std::vector<std::string> ProcToProcReader::getDirectP1ByP2(
    const std::string& proc2) {
  if (!store.hasDirectAncestors(proc2)) {
    return {};
  }
  const auto& rawRes = store.getDirectAncestors(proc2);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::string> ProcToProcReader::getTransitiveP1ByP2(
    const std::string& proc2) {
  if (!store.hasAncestorsT(proc2)) {
    return {};
  }
  const auto& rawRes = store.getAncestorsT(proc2);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::string> ProcToProcReader::getDirectP2ByP1(
    const std::string& proc1) {
  if (!store.hasDirectSuccessors(proc1)) {
    return {};
  }
  const auto& rawRes = store.getDirectSuccessors(proc1);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::string> ProcToProcReader::getTransitiveP2ByP1(
    const std::string& proc1) {
  if (!store.hasSuccessorsT(proc1)) {
    return {};
  }
  const auto& rawRes = store.getSuccessorsT(proc1);
  return {rawRes.begin(), rawRes.end()};
}

std::vector<std::pair<std::string, std::string>>
ProcToProcReader::getDirectP1AndP2Pairs() {
  const auto& rawRes = store.getDirectSuccessorMap();
  return CollectionUtils::mapSetToPairVector<std::string, std::string>(rawRes);
}

std::vector<std::pair<std::string, std::string>>
ProcToProcReader::getTransitiveP1AndP2Pairs() {
  return CollectionUtils::mapSetToPairVector(store.getRelationsT());
}

bool ProcToProcReader::hasDirectRelation(const std::string& proc1,
                                         const std::string& proc2) {
  return store.hasDirectRelation(proc1, proc2);
}

bool ProcToProcReader::hasTransitiveRelation(const std::string& proc1,
                                             const std::string& proc2) {
  return store.hasRelationT(proc1, proc2);
}
