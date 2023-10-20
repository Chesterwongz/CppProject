#include "CallsAbstraction.h"

/**
 * Calls abstraction:
* - firstArg: Synonym (Proc) OR Identifier (Proc) OR Wildcard
* - secondArg: Synonym (Proc) OR Identifier (Proc) OR Wildcard
 */

vector<pair<string, string>> CallsAbstraction::getAllAbstractionPairs() {
  return pkb.getCallPairs();
}

vector<string> CallsAbstraction::getFirstProcInAbstraction(
    const string& secondProcName) {
  return pkb.getCallerProcs(secondProcName);
}

vector<string> CallsAbstraction::getSecondProcInAbstraction(
    const string& firstProcName) {
  return pkb.getCalleeProcs(firstProcName);
}

bool CallsAbstraction::isProcRelatedToProc(const string& firstProcName,
                                           const string& secondProcName) {
  return pkb.hasCalls(firstProcName, secondProcName);
}
