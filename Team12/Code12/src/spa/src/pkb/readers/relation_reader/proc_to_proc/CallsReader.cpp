#include "CallsReader.h"

std::vector<std::string> CallsReader::getCallerProcs(const std::string& proc1) {
  auto filter = PredicateUtils::truePredicate<std::string>();

  auto res = callsStore.getDirectAncestor(proc1, filter);

  return res;
}

std::vector<std::string> CallsReader::getCallerProcsStar(
    const std::string& proc1) {
  auto filter = PredicateUtils::truePredicate<std::string>();

  auto res = callsStore.getAncestorsOf(proc1, filter);

  return res;
}

std::vector<std::string> CallsReader::getCalleeProcs(const std::string& proc2) {
  auto filter = PredicateUtils::truePredicate<std::string>();

  auto res = callsStore.getDirectSuccessor(proc2, filter);

  return res;
}

std::vector<std::string> CallsReader::getCalleeProcsStar(
    const std::string& proc2) {
  auto filter = PredicateUtils::truePredicate<std::string>();

  auto res = callsStore.getSuccessorsOf(proc2, filter);

  return res;
}

std::vector<std::pair<std::string, std::string>> CallsReader::getCallPairs() {
  auto filter = PredicateUtils::truePredicate<std::string>();
  auto filterPair = std::make_pair(filter, filter);

  auto res = callsStore.getAllRelations(filterPair);

  return res;
}

std::vector<std::pair<std::string, std::string>>
CallsReader::getCallsStarPairs() {
  auto filter = PredicateUtils::truePredicate<std::string>();
  auto filterPair = std::make_pair(filter, filter);

  auto res = callsStore.getAllRelationsT(filterPair);

  return res;
}

bool CallsReader::hasCalls(const std::string& proc1, const std::string& proc2) {
  return callsStore.hasDirectRelation(proc1, proc2);
}

bool CallsReader::hasCallsT(const std::string& proc1,
                            const std::string& proc2) {
  return callsStore.hasRelationT(proc1, proc2);
}
