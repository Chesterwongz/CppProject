#include "CallsStarAbstraction.h"

/**
 * Calls Star abstraction:
 * - firstArg: Synonym (Proc) OR Identifier (Proc) OR Wildcard
 * - secondArg: Synonym (Proc) OR Identifier (Proc) OR Wildcard
 */
bool CallsStarAbstraction::hasPairs() { return this->pkb.hasCallsT(); }

vector<pair<string, string>> CallsStarAbstraction::getAllAbstractionPairs() {
  return pkb.getCallsStarPairs();
}

vector<string> CallsStarAbstraction::getFirstProcInAbstraction(
    const string& secondProcName) {
  return pkb.getCallerProcsStar(secondProcName);
}

vector<string> CallsStarAbstraction::getSecondProcInAbstraction(
    const string& firstProcName) {
  return pkb.getCalleeProcsStar(firstProcName);
}

bool CallsStarAbstraction::isProcRelatedToProc(const string& firstProcName,
                                               const string& secondProcName) {
  return pkb.hasCallsT(firstProcName, secondProcName);
}
