#include "SemanticValidator.h"

SemanticValidator::SemanticValidator() = default;

void SemanticValidator::validate(const TNode* root) {
    initialiseGraph(root);
    dfs(root);
    if (hasCyclicCalls()) {
        throw CyclicProcCallException();
    }
}

bool SemanticValidator::isProcedureDefined(const string &procName) {
    return indegree.find(procName) != indegree.end();
}

void SemanticValidator::initialiseGraph(const TNode* root) {
    auto programNode = dynamic_cast<const ProgramNode*>(root);
    assert(programNode);
    vector<std::string> procNames = programNode->getProcNames();
    for (auto &procName : procNames) {
        if (isProcedureDefined(procName)) {
            // duplicate proc name
            throw DuplicateProcNameException(procName);
        }
        adjList[procName] = std::unordered_set<std::string>();
        indegree[procName] = 0;
    }
}

bool SemanticValidator::isDuplicateCall(const string &callee) {
    return adjList[callerProc].find(callee) != adjList[callerProc].end();
}

void SemanticValidator::updateGraph(const std::string& callee) {
    if (!isProcedureDefined(callee)) {
        // undefined proc called
        throw UndefinedProcCallException(callee);
    }
    if (isDuplicateCall(callee)) {
        return;
    }
    indegree[callee]++;
    adjList[callerProc].insert(callee);
}

bool SemanticValidator::hasCyclicCalls() {
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
    return countVisited != indegree.size();
}

void SemanticValidator::dfs(const TNode* node) {
    if (!node) return;
    switch (node->getType()) {
        case TNodeType::TNODE_PROCEDURE:
            callerProc = node->getValue();
            break;

        case TNodeType::TNODE_CALL:
            updateGraph(node->getValue());
            break;

        default:
            break;
    }
    for (auto &child : node->getChildren()) {
        dfs(child);
    }
}
