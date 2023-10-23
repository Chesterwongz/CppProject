#include "FollowsExtractor.h"

FollowsExtractor::FollowsExtractor(PKBWriter& pkbWriter)
    : Extractor(pkbWriter) {}

void FollowsExtractor::visitAssign(const AssignNode& node) {
  processCurrStmt(node);
}

void FollowsExtractor::visitCall(const CallNode& node) {
  processCurrStmt(node);
}

void FollowsExtractor::visitIf(const IfNode& node) { processCurrStmt(node); }

void FollowsExtractor::visitPrint(const PrintNode& node) {
  processCurrStmt(node);
}

void FollowsExtractor::visitRead(const ReadNode& node) {
  processCurrStmt(node);
}

void FollowsExtractor::visitWhile(const WhileNode& node) {
  processCurrStmt(node);
}

void FollowsExtractor::visitStmtList(const StmtListNode& node) {
  nestingBlocksStack.push(common::INVALID_STMT_NUM);  // new nesting block
}

void FollowsExtractor::postVisitStmtList(const StmtListNode& node) {
  nestingBlocksStack.pop();  // remove nesting block
}

void FollowsExtractor::processCurrStmt(const StmtNode& node) {
  int currLine = node.getLineNum();
  int prevLine = nestingBlocksStack.top();
  if (prevLine != common::INVALID_STMT_NUM) {
    pkbWriter.addFollows(prevLine, currLine);
  }
  nestingBlocksStack.pop();
  nestingBlocksStack.push(currLine);
}
