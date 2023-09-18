#include "CallsExtractor.h"

CallsExtractor::CallsExtractor(PKBWriter *pkbWriter) : Extractor(pkbWriter) {}

void CallsExtractor::visitProgram(const ProgramNode *node) {
    vector<std::string> procNames = node->getProcNames();
    for (auto &procName : procNames) {
        adjList[procName] = std::unordered_set < std::string > ();
        indegree[procName] = 0;
    }
}

void CallsExtractor::visitProcedure(const ProcNode *node) {
    currProc = node->getValue();
}

void CallsExtractor::visitCall(const CallNode *node) {
    std::string callee = node->getValue();
    if (indegree.find(callee) == indegree.end()) {
        // undefined proc called
        throw UndefinedProcCallException(callee);
    }

    indegree[callee]++;
    adjList[currProc].insert(callee);
    pkbWriter->setCallsRelationship(currProc, callee);
}

void CallsExtractor::postVisitProgram(const ProgramNode *node) {
    // check for cyclic calls using topo sort
    std::queue<std::string> q;
    for (auto &it : indegree) {
        if (it.second == 0) {
            q.push(it.first);
        }
    }
    int countVisited = 0;
    while (!q.empty()) {
        std::string curr = q.front();
        q.pop();
        countVisited++;
        for (auto &callee : adjList[curr]) {
            indegree[callee]--;
            if (indegree[callee] == 0) {
                q.push(callee);
            }
        }
    }
    if (countVisited != indegree.size()) {
        throw CyclicProcCallException();
    }
}
