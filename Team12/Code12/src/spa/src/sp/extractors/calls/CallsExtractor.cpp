#include "CallsExtractor.h"

CallsExtractor::CallsExtractor(PKBWriter& pkbWriter) : Extractor(pkbWriter) {}

void CallsExtractor::visitProcedure(const ProcNode& node) {
    currProc = node.getValue();
}

void CallsExtractor::visitCall(const CallNode& node) {
    std::string callee = node.getValue();
    callerToCalleeMap[currProc].insert(callee);
    //pkbWriter.setCallsRelationship(currProc, callee);
}

void CallsExtractor::postVisitProgram(const ProgramNode& node) {
    addCallsStar();
}

void CallsExtractor::addCallsStar() {
    for (const auto& pair : callerToCalleeMap) {
        std::string caller = pair.first;
        std::unordered_set<std::string> callees = pair.second;
        std::unordered_set<std::string> allCallees;
        std::queue<std::string> toVisit;
        for (const auto& callee : callees) {
            toVisit.push(callee);
        }

        while (!toVisit.empty()) {
            std::string curr = toVisit.front();
            toVisit.pop();
            if (allCallees.find(curr) != allCallees.end()) {
                // already inserted curr callee
                continue;
            }
            allCallees.insert(curr);
            for (const auto& next : callerToCalleeMap[curr]) {
                toVisit.push(next);
            }
        }

        for (const auto& callee : allCallees) {
            //pkbWriter.setCallsStarRelationship(caller, callee);
        }
    }
}
