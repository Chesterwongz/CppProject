#pragma once

#include <unordered_set>
#include <set>
#include <map>
#include <vector>
#include <string>
#include "Extractor.h"
#include "sp/ast/ProcNode.h"
#include "sp/ast/statements/AssignNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/ast/statements/PrintNode.h"
#include "sp/ast/expressions/VarNode.h"

struct UsesStmtState {
    int lineNum;
    std::unordered_set<std::string> varsUsed;
    bool isAnticipateAssignLhs = false;
};

class UsesExtractor : public Extractor {
private:
    std::vector<UsesStmtState> stmtStates;
    std::string procName;
    void processCurrState();
    void postVisit();
    void addUses(int lineNum, const std::string &var);

public:
    explicit UsesExtractor(PKBWriter *pkbWriter);
    void visitProcedure(const ProcNode *node) override; // TODO: modify after MS1
    void visitAssign(const AssignNode *node) override;
    void visitIf(const IfNode *node) override;
    void visitWhile(const WhileNode *node) override;
    void visitPrint(const PrintNode *node) override;
    void visitVariable(const VarNode *node) override;
    void postVisitAssign(const AssignNode *node) override;
    void postVisitIf(const IfNode *node) override;
    void postVisitWhile(const WhileNode *node) override;
    void postVisitPrint(const PrintNode *node) override;
};
