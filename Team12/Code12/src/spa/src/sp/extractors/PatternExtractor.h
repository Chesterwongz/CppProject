#pragma once

#include <string>
#include <unordered_set>
#include "Extractor.h"
#include "sp/ast/statements/AssignNode.h"
#include "sp/ast/statements/WhileNode.h"
#include "sp/ast/statements/IfNode.h"

class PatternExtractor : public Extractor {
private:
    std::string nodeToPostfixString(const TNode *node);
    void getControlVars(std::unordered_set<std::string>& vars, const TNode *node);
    void processContainerStmt(StmtType stmtType, const StmtNode *node);

public:
    explicit PatternExtractor(PKBWriter *pkbWriter);
    void visitAssign(const AssignNode *node) override;
    void visitWhile(const WhileNode *node) override;
    void visitIf(const IfNode *node) override;

};

