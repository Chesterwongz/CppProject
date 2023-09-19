#include "EntityExtractor.h"

EntityExtractor::EntityExtractor(PKBWriter *pkbWriter) : Extractor(pkbWriter) {}

void EntityExtractor::visitAssign(const AssignNode& node) {
    pkbWriter->setStatement(node.getLineNum(), StmtType::ASSIGN);
}

void EntityExtractor::visitCall(const CallNode& node) {
    pkbWriter->setStatement(node.getLineNum(), StmtType::CALL);
}

void EntityExtractor::visitIf(const IfNode& node) {
    pkbWriter->setStatement(node.getLineNum(), StmtType::IF);
}

void EntityExtractor::visitPrint(const PrintNode& node) {
    pkbWriter->setStatement(node.getLineNum(), StmtType::PRINT);
}

void EntityExtractor::visitRead(const ReadNode& node) {
    pkbWriter->setStatement(node.getLineNum(), StmtType::READ);
}

void EntityExtractor::visitWhile(const WhileNode& node) {
    pkbWriter->setStatement(node.getLineNum(), StmtType::WHILE);
}

void EntityExtractor::visitVariable(const VarNode& node) {
    pkbWriter->setVariable(node.getValue());
}

void EntityExtractor::visitConstant(const ConstNode& node) {
    pkbWriter->setConstant(node.getValue());
}

void EntityExtractor::visitProcedure(const ProcNode& node) {
    pkbWriter->setProcedure(node.getValue(), node.getProcStart());
}
