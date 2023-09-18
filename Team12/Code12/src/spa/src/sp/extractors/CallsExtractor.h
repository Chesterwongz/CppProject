#pragma once

#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Extractor.h"
#include "sp/ast/ProgramNode.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/statements/CallNode.h"
#include "sp/exceptions/CyclicProcCallException.h"
#include "sp/exceptions/UndefinedProcCallException.h"


class CallsExtractor : public Extractor {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> adjList;
    std::unordered_map<std::string, int> indegree;
    std::string currProc;
    bool isProcedureDefined(const std::string &procName);
    bool hasCyclicCalls();

public:
    explicit CallsExtractor(PKBWriter *pkbWriter);
    void visitProgram(const ProgramNode *node) override;
    void visitProcedure(const ProcNode *node) override;
    void visitCall(const CallNode *node) override;
    void postVisitProgram(const ProgramNode *node) override;
};
