#pragma once

#include "pkb/PkbWriter.h"

class TNode;
class ProgramNode;
class ProcNode;
class StmtListNode;
class StmtNode;
class AssignNode;
class CallNode;
class IfNode;
class PrintNode;
class ReadNode;
class WhileNode;
class CondNode;
class ExprNode;
class VarNode;
class ConstNode;

class Extractor {
private:
    PkbWriter* pkbWriter;

public:
    explicit Extractor(): pkbWriter() {};
    virtual ~Extractor() = default;
    explicit Extractor(PkbWriter* pkbWriter): pkbWriter(pkbWriter) {};
    virtual void visitProgram(const ProgramNode* node) {};
    virtual void visitProcedure(const ProcNode* node) {};
    virtual void postVisitProcedure(const ProcNode* node) {};
    virtual void visitStmtList(const StmtListNode* node) {};
    virtual void postVisitStmtList(const StmtListNode* node) {};

    virtual void visitAssign(const AssignNode* node) {};
    virtual void visitCall(const CallNode* node) {};

    virtual void visitIf(const IfNode* node) {};
    virtual void postVisitIf(const IfNode* node) {};

    virtual void visitPrint(const PrintNode* node) {};
    virtual void visitRead(const ReadNode* node) {};
    virtual void visitWhile(const WhileNode* node) {};
    virtual void postVisitWhile(const WhileNode* node) {};

    virtual void visitCond(const CondNode* node) {};
    virtual void visitExpr(const ExprNode* node) {};

    virtual void visitVariable(const VarNode* node) {};
    virtual void visitConstant(const ConstNode* node) {};
};
