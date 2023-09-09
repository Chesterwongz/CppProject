#pragma once

#include <map>
#include <set>
#include <unordered_set>
#include <stack>
#include <vector>
#include "Extractor.h"
#include "sp/ast/statements/AssignNode.h"
#include "sp/ast/statements/CallNode.h"
#include "sp/ast/statements/IfNode.h"
#include "sp/ast/statements/PrintNode.h"
#include "sp/ast/statements/ReadNode.h"
#include "sp/ast/statements/StmtNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/ast/expressions/VarNode.h"
#include "sp/ast/expressions/ConstNode.h"
#include "sp/ast/ProcNode.h"

class EntityExtractor : public Extractor {
private:
    // temp storage for testing
    // TODO: change to use PkbWriter
    std::unordered_set<std::string> variables;
    std::unordered_set<std::string> constants;
    std::unordered_set<std::string> procedures;
    std::unordered_set<int> assignStmts;
    std::unordered_set<int> callStmts;
    std::unordered_set<int> ifStmts;
    std::unordered_set<int> printStmts;
    std::unordered_set<int> readStmts;
    std::unordered_set<int> whileStmts;

public:
    EntityExtractor(); // TODO: remove this constructor after pkb integration
    explicit EntityExtractor(PkbWriter *pkbWriter);
    void visitAssign(const AssignNode *node) override;
    void visitCall(const CallNode *node) override;
    void visitIf(const IfNode *node) override;
    void visitPrint(const PrintNode *node) override;
    void visitRead(const ReadNode *node) override;
    void visitWhile(const WhileNode *node) override;
    void visitVariable(const VarNode *node) override;
    void visitConstant(const ConstNode *node) override;
    void visitProcedure(const ProcNode *node) override;

    std::unordered_set<std::string> getVariables(); // TODO: remove this method after pkb integration
    std::unordered_set<std::string> getConstants(); // TODO: remove this method after pkb integration
    std::unordered_set<std::string> getProcedures(); // TODO: remove this method after pkb integration
    std::unordered_set<int> getAssignStmts();
    std::unordered_set<int> getCallStmts();
    std::unordered_set<int> getIfStmts();
    std::unordered_set<int> getPrintStmts();
    std::unordered_set<int> getReadStmts();
    std::unordered_set<int> getWhileStmts();

};
