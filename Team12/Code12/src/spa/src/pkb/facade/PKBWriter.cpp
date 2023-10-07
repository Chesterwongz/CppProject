#include "PKBWriter.h"

void PKBWriter::setFollowsRelationship(int statementNumber,
                                       int followingStatement) {
  storage.setFollows(statementNumber, followingStatement);
}

void PKBWriter::setModifiesRelationship(const string &variableName,
                                        int statementNumber) {
  storage.setVariableModification(variableName, statementNumber);
}

void PKBWriter::setParentRelationship(int statementNumber, int childStatement) {
  storage.setParent(statementNumber, childStatement);
}

void PKBWriter::setParentStarRelationship(int statementNumber,
                                          int childStatement) {
  storage.setParentStar(statementNumber, childStatement);
}

void PKBWriter::setUsesRelationship(const string &variableName,
                                    int statementNumber) {
  storage.setVariableUsage(variableName, statementNumber);
}

void PKBWriter::setStatement(int statementNumber, StmtType statementType) {
  storage.setStatement(statementNumber, statementType);
}

void PKBWriter::setVariable(const string &variableName) {
  storage.setVariable(variableName);
}

void PKBWriter::setConstant(const string &constantValue) {
  storage.setConstant(constantValue);
}

void PKBWriter::setProcedure(const string &procedureName, int startStatement) {
  storage.setProcedure(procedureName, startStatement);
}

void PKBWriter::setAssignPattern(const string &variableName, const string &rpn,
                                 int statementNumber) {
  storage.setAssignPattern(variableName, rpn, statementNumber);
}
void PKBWriter::setWhilePattern(int statementNumber, const string &varName) {}

void PKBWriter::setIfPattern(int statementNumber, const string &varName) {}

void PKBWriter::setUsesRelationship(const string &variableName,
                                    const string &procName) {
  storage.setVariableUsage(variableName, procName);
}

void PKBWriter::setModifiesRelationship(const string &variableName,
                                        const string &procName) {
  storage.setVariableModification(variableName, procName);
}

void PKBWriter::setUsesForCalls(const string &callerProc,
                                const string &calleeProc) {
  unordered_set<string> usedVars = storage.getUsedVariablesForProc(calleeProc);
  for (const auto &var : usedVars) {
    setUsesRelationship(var, callerProc);
  }
}

void PKBWriter::setModifiesForCalls(const string &callerProc,
                                    const string &calleeProc) {
  unordered_set<string> modifiedVars =
      storage.getModifiedVariablesForProc(calleeProc);
  for (const auto &var : modifiedVars) {
    setModifiesRelationship(var, callerProc);
  }
}

void PKBWriter::setRelationshipsForIndirectCalls(
    const string &caller, const unordered_set<pair<string, string>, PairUtils::PairHash> &visitedCallees) {
  for (const auto &[stmtNum, callee] : visitedCallees) {
    setCallsStarRelationship(caller, callee, std::stoi(stmtNum));
    setModifiesForCalls(caller, callee);
    setUsesForCalls(caller, callee);
  }
}

// void PKBWriter::setIndirectCallsRelationship() {
//   const auto &callerToCalleeMap = storage.getCallsMap();
//   for (const auto &[caller, directCallees] : callerToCalleeMap) {
//     unordered_set<string> visitedCallees;
//     queue<string> toVisit;
//     for (const auto &callee : directCallees) {
//       toVisit.push(callee);
//     }
//     while (!toVisit.empty()) {
//       string curr = toVisit.front();
//       toVisit.pop();
//       if (visitedCallees.find(curr) != visitedCallees.end()) {
//         // already inserted curr callee
//         continue;
//       }
//       visitedCallees.insert(curr);
//       unordered_set<string> allCalleesOfCurr =
//           storage.getAllProcsCalledBy(curr);
//       if (!allCalleesOfCurr.empty()) {
//         // already computed transitive calls by curr
//         visitedCallees.insert(allCalleesOfCurr.begin(),
//         allCalleesOfCurr.end()); continue;
//       }
//
//       for (const auto &next : storage.getDirectProcsCalledBy(curr)) {
//         toVisit.push(next);
//       }
//     }
//     setRelationshipsForIndirectCalls(caller, visitedCallees);
//   }
// }

unordered_set<pair<string, string>, PairUtils::PairHash> PKBWriter::getIndirectCallees(int stmtNum, const string &proc) {
  vector<pair<string, string>> cached = storage.getCalledStarBy(proc);
  unordered_set<pair<string, string>, PairUtils::PairHash> visitedCallees;
  if (!cached.empty()) {
    visitedCallees.insert(cached.begin(), cached.end());
    return visitedCallees;
  }
  queue<pair<string, string>> toVisit;
  toVisit.emplace(std::to_string(stmtNum), proc);
  while (!toVisit.empty()) {
    pair<string, string> curr = toVisit.front();
    const string& currProc = curr.second;
    toVisit.pop();
    if (visitedCallees.find(curr) != visitedCallees.end()) {
      continue;
    }
    visitedCallees.insert(curr);
    vector<pair<string, string>> allCalleesOfCurr = storage.getCalledStarBy(currProc);
    if (!allCalleesOfCurr.empty()) {
      // already computed transitive calls by curr
      visitedCallees.insert(allCalleesOfCurr.begin(), allCalleesOfCurr.end());
      continue;
    }
    for (const auto &[nextStmt, nextProc] : storage.getCalledBy(currProc)) {
      toVisit.emplace(nextStmt, nextProc);
    }
  }
  for (const auto &[calleeStmt, calleeProc] : visitedCallees) {
    setCallsStarRelationship(proc, calleeProc, std::stoi(calleeStmt));
  }
  return visitedCallees;
}

void PKBWriter::setIndirectCallsRelationship() {
  const auto &callerToCalleeMap = storage.getCallsMap();
  for (const auto &[caller, directStmtCallees] : callerToCalleeMap) {
    unordered_set<pair<string, string>, PairUtils::PairHash> visitedCallees;
    for (const auto &[stmtNum, callee] : directStmtCallees) {
      auto indirectCalleesOfCallee = getIndirectCallees(stmtNum, callee);
      visitedCallees.insert(indirectCalleesOfCallee.begin(),
                            indirectCalleesOfCallee.end());
    }
    setRelationshipsForIndirectCalls(caller, visitedCallees);
  }
}

void PKBWriter::setCallsRelationship(const string &callerProc,
                                     const string &calleeProc, int stmtNum) {}

void PKBWriter::setCallsStarRelationship(const string &callerProc,
                                         const string &calleeProc,
                                         int stmtNum) {}

void PKBWriter::setCFG(const std::string &procName, unique_ptr<CFG> cfg) {}
