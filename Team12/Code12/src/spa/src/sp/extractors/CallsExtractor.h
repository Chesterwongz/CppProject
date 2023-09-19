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
    std::string currProc;
    std::unordered_map<std::string, std::unordered_set<std::string>> callerToCalleeMap;
    void addCallsStar();

public:
    explicit CallsExtractor(PKBWriter& pkbWriter);
    void visitProcedure(const ProcNode& node) override;
    void visitCall(const CallNode& node) override;
    void postVisitProgram(const ProgramNode& node) override;
};
