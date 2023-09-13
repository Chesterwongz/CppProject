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
#include "sp/ast/terminals/VarNode.h"
#include "sp/ast/terminals/ConstNode.h"
#include "sp/ast/ProcNode.h"
#include "pkb/facade/PKBWriter.h"

class EntityExtractor : public Extractor {
public:
    explicit EntityExtractor(PKBWriter *pkbWriter);
    void visitAssign(const AssignNode *node) override;
    void visitCall(const CallNode *node) override;
    void visitIf(const IfNode *node) override;
    void visitPrint(const PrintNode *node) override;
    void visitRead(const ReadNode *node) override;
    void visitWhile(const WhileNode *node) override;
    void visitVariable(const VarNode *node) override;
    void visitConstant(const ConstNode *node) override;
    void visitProcedure(const ProcNode *node) override;
};
