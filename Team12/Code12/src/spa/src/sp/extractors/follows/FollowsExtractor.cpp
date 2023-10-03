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
  nestingBlocksStack.emplace();  // add new nesting block
}

void FollowsExtractor::postVisitStmtList(const StmtListNode& node) {
  nestingBlocksStack.pop();  // remove nesting block
}

void FollowsExtractor::processCurrStmt(const StmtNode& node) {
  // ai-gen start(gpt-4, 2)
  int currLine = node.getLineNum();
  // Update the Follows* relationships for prev lines in this block
  for (const int& prevLine : nestingBlocksStack.top()) {
    addFollows(prevLine, currLine);
  }
  nestingBlocksStack.top().push_back(currLine);
  // ai-gen end
}

void FollowsExtractor::addFollows(int prevLine, int currLine) {
  pkbWriter.setFollowsRelationship(prevLine, currLine);
}
