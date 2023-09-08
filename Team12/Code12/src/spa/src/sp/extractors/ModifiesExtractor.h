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
#include "sp/ast/statements/ReadNode.h"
#include "sp/ast/expressions/VarNode.h"

struct ModifiesStmtState {
    int lineNum;
    std::unordered_set<std::string> varsModified;
    bool isAnticipateVar = false;
};

class ModifiesExtractor : public Extractor {
private:
    std::vector<ModifiesStmtState> stmtStates;
    std::string procName;
    void processCurrState();
    void postVisit();
    std::map<std::string, std::set<int>> modifiesMap; // var, stmts

public:
    ModifiesExtractor();
    explicit ModifiesExtractor(PkbWriter *pkbWriter);
    void visitProcedure(const ProcNode *node) override; // TODO: modify after MS1
    void visitAssign(const AssignNode *node) override;
    void visitIf(const IfNode *node) override;
    void visitWhile(const WhileNode *node) override;
    void visitRead(const ReadNode *node) override;
    void visitVariable(const VarNode *node) override;
    void postVisitAssign(const AssignNode *node) override;
    void postVisitIf(const IfNode *node) override;
    void postVisitWhile(const WhileNode *node) override;
    void postVisitRead(const ReadNode *node) override;
    void addModifies(int lineNum, const std::string &var);
    std::map<std::string, std::set<int>> getModifiesMap();
};
