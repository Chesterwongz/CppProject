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
    const string &caller,
    const unordered_set<pair<string, string>, PairUtils::PairHash>
        &visitedCallees) {
  for (const auto &[stmtNum, callee] : visitedCallees) {
    setCallsStarRelationship(caller, callee, std::stoi(stmtNum));
    setModifiesForCalls(caller, callee);
    setUsesForCalls(caller, callee);
  }
}

void PKBWriter::setIndirectCallsRelationship() {
  const auto &callerToCalleeMap = storage.getCalleeProcsMap();
  for (const auto &[caller, directStmtCallees] : callerToCalleeMap) {
    unordered_set<pair<string, string>, PairUtils::PairHash> visitedCallees;
    queue<pair<string, string>> toVisit;

    for (const auto &[stmtNum, callee] : directStmtCallees) {
      toVisit.emplace(std::to_string(stmtNum), callee);
    }
    while (!toVisit.empty()) {
      pair<string, string> curr = toVisit.front();
      string currProc = curr.second;
      toVisit.pop();
      if (visitedCallees.find(curr) != visitedCallees.end()) {
        // already inserted curr callee
        continue;
      }
      visitedCallees.insert(curr);
      vector<pair<string, string>> allCalleesOfCurr =
          storage.getCalleeProcsStar(currProc);
      if (!allCalleesOfCurr.empty()) {
        // already computed transitive calls by curr
        visitedCallees.insert(allCalleesOfCurr.begin(), allCalleesOfCurr.end());
        continue;
      }

      for (const auto &[stmtNum, callee] : storage.getCalleeProcs(currProc)) {
        toVisit.emplace(stmtNum, callee);
      }
    }
    setRelationshipsForIndirectCalls(caller, visitedCallees);
  }
}

void PKBWriter::setCallsRelationship(const string &callerProc,
                                     const string &calleeProc, int stmtNum) {
  storage.setCallsRelationship(callerProc, calleeProc, stmtNum);
}

void PKBWriter::setCallsStarRelationship(const string &callerProc,
                                         const string &calleeProc,
                                         int stmtNum) {
  storage.setCallsStarRelationship(callerProc, calleeProc, stmtNum);
}

void PKBWriter::setCFG(const std::string &procName, unique_ptr<CFG> cfg) {}
