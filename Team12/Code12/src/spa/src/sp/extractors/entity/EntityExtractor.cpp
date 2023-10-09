#include "EntityExtractor.h"

EntityExtractor::EntityExtractor(PKBWriter& pkbWriter) : Extractor(pkbWriter) {}

void EntityExtractor::processStmt(int lineNum, StmtType type) {
  currLine = lineNum;
  pkbWriter.setStatement(currLine, type);
  pkbWriter.setProcForStmt(currProc, currLine);
}

void EntityExtractor::visitAssign(const AssignNode& node) {
  processStmt(node.getLineNum(), StmtType::ASSIGN);
}

void EntityExtractor::visitCall(const CallNode& node) {
  processStmt(node.getLineNum(), StmtType::CALL);
}

void EntityExtractor::visitIf(const IfNode& node) {
  processStmt(node.getLineNum(), StmtType::IF);
}

void EntityExtractor::visitPrint(const PrintNode& node) {
  processStmt(node.getLineNum(), StmtType::PRINT);
}

void EntityExtractor::visitRead(const ReadNode& node) {
  processStmt(node.getLineNum(), StmtType::READ);
}

void EntityExtractor::visitWhile(const WhileNode& node) {
  processStmt(node.getLineNum(), StmtType::WHILE);
}

void EntityExtractor::visitVariable(const VarNode& node) {
  pkbWriter.setVariable(node.getValue());
}

void EntityExtractor::visitConstant(const ConstNode& node) {
  pkbWriter.setConstant(node.getValue());
}

void EntityExtractor::visitProcedure(const ProcNode& node) {
  currProc = node.getValue();
}
