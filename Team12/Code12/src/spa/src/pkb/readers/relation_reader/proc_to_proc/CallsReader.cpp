#include "CallsReader.h"

std::vector<std::string> CallsReader::getCallerProcs(const std::string& proc2) {
  return reader.getDirectP1ByP2(proc2);
}

std::vector<std::string> CallsReader::getCallerProcsStar(
    const std::string& proc2) {
  return reader.getTransitiveP1ByP2(proc2);
}

std::vector<std::string> CallsReader::getCalleeProcs(const std::string& proc1) {
  return reader.getDirectP2ByP1(proc1);
}

std::vector<std::string> CallsReader::getCalleeProcsStar(
    const std::string& proc1) {
  return reader.getTransitiveP2ByP1(proc1);
}

std::vector<std::pair<std::string, std::string>> CallsReader::getCallPairs() {
  return reader.getDirectP1AndP2Pairs();
}

std::vector<std::pair<std::string, std::string>>
CallsReader::getCallsStarPairs() {
  return reader.getTransitiveP1AndP2Pairs();
}

bool CallsReader::hasCalls(const std::string& proc1, const std::string& proc2) {
  return reader.hasDirectRelation(proc1, proc2);
}

bool CallsReader::hasCallsT(const std::string& proc1,
                            const std::string& proc2) {
  return reader.hasTransitiveRelation(proc1, proc2);
}

bool CallsReader::hasCalls() {
  return reader.hasDirectP1AndP2Pairs();
}

bool CallsReader::hasCallsT() {
  return reader.hasTransitiveP1AndP2Pairs();
}
