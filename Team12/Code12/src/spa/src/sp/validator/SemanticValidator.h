#pragma once

#include <queue>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "sp/ast/TNode.h"
#include "sp/ast/ProgramNode.h"
#include "sp/exceptions/UndefinedProcCallException.h"
#include "sp/exceptions/CyclicProcCallException.h"


class SemanticValidator {
private:
    TNode* root;
    std::string callerProc;
    std::unordered_map<std::string, std::unordered_set<std::string>> adjList;
    std::unordered_map<std::string, int> indegree;
    void initialiseGraph();
    void updateGraph(const std::string& callee);
    bool isProcedureDefined(const std::string &procName);
    bool isDuplicateCall(const string &callee);
    bool hasCyclicCalls();
    void dfs(const TNode* node);

public:
    explicit SemanticValidator(TNode* root);
    void validate();
};

