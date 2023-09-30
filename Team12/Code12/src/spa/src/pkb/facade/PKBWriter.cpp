#include "PKBWriter.h"

void PKBWriter::setFollowsRelationship(int statementNumber,
                                       int followingStatement) {
    storage.setFollows(statementNumber, followingStatement);
}

void PKBWriter::setModifiesRelationship(const std::string &variableName,
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

void PKBWriter::setUsesRelationship(const std::string &variableName,
                                    int statementNumber) {
    storage.setVariableUsage(variableName, statementNumber);
}

void PKBWriter::setStatement(int statementNumber, StmtType statementType) {
    storage.setStatement(statementNumber, statementType);
}

void PKBWriter::setVariable(const std::string &variableName) {
    storage.setVariable(variableName);
}

void PKBWriter::setConstant(const std::string &constantValue) {
    storage.setConstant(constantValue);
}

void PKBWriter::setProcedure(const std::string &procedureName,
                             int startStatement) {
    storage.setProcedure(procedureName, startStatement);
}

void PKBWriter::setAssignPattern(const std::string &variableName, const std::string &rpn, int statementNumber) {
    storage.setAssignPattern(variableName, rpn, statementNumber);
}
void PKBWriter::setWhilePattern(int statementNumber, const std::string &varName) {}

void PKBWriter::setIfPattern(int statementNumber, const std::string &varName) {}

void PKBWriter::setUsesRelationship(const std::string &variableName, const std::string &procName) {
    storage.setVariableUsage(variableName, procName);
}

void PKBWriter::setModifiesRelationship(const std::string &variableName, const std::string &procName) {
    storage.setVariableModification(variableName, procName);
}

void PKBWriter::setUsesForCalls(const std::string &callerProc, const std::string &calleeProc) {
    std::unordered_set<std::string> usedVars = storage.getUsedVariablesForProc(calleeProc);
    for (const auto &var : usedVars) {
        setUsesRelationship(var, callerProc);
    }
}

void PKBWriter::setModifiesForCalls(const std::string &callerProc,
                                    const std::string &calleeProc) {
    std::unordered_set<std::string> modifiedVars = storage.getModifiedVariablesForProc(calleeProc);
    for (const auto &var : modifiedVars) {
        setModifiesRelationship(var, callerProc);
    }
}

void PKBWriter::setRelationshipsForIndirectCalls(
    const string &caller,
    const std::unordered_set<std::string> &visitedCallees) {
    for (const auto &callee : visitedCallees) {
        setCallsStarRelationship(caller, callee);
        setModifiesForCalls(caller, callee);
        setUsesForCalls(caller, callee);
    }
}

void PKBWriter::setIndirectCallsRelationship() {
    const auto &callerToCalleeMap = storage.getCallsMap();
    for (const auto &pair : callerToCalleeMap) {
        std::string caller = pair.first;
        std::unordered_set<std::string> directCallees = pair.second;
        std::unordered_set<std::string> visitedCallees;
        std::queue<std::string> toVisit;
        for (const auto &callee : directCallees) {
            toVisit.push(callee);
        }
        while (!toVisit.empty()) {
            std::string curr = toVisit.front();
            toVisit.pop();
            if (visitedCallees.find(curr) != visitedCallees.end()) {
                // already inserted curr callee
                continue;
            }
            visitedCallees.insert(curr);
            std::unordered_set<std::string> allCalleesOfCurr = storage.getAllProcsCalledBy(curr);
            if (!allCalleesOfCurr.empty()) {
                // already computed transitive calls by curr
                visitedCallees.insert(allCalleesOfCurr.begin(), allCalleesOfCurr.end());
                continue;
            }

            for (const auto &next : storage.getDirectProcsCalledBy(curr)) {
                toVisit.push(next);
            }
        }
        setRelationshipsForIndirectCalls(caller, visitedCallees);
    }
}

void PKBWriter::setCallsRelationship(const string &callerProc,
                                     const string &calleeProc) {}

void PKBWriter::setCallsStarRelationship(const std::string &callerProc,
                                         const std::string &calleeProc) {}