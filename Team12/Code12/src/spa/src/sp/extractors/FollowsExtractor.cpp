#include "FollowsExtractor.h"

FollowsExtractor::FollowsExtractor(PKBWriter *pkbWriter) : Extractor(pkbWriter) {}

void FollowsExtractor::visitAssign(const AssignNode& node) {
    processCurrStmt(node);
}

void FollowsExtractor::visitCall(const CallNode& node) {
    processCurrStmt(node);
}

void FollowsExtractor::visitIf(const IfNode& node) {
    processCurrStmt(node);
}

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
    nestingBlocksStack.emplace(); // add new nesting block
}

void FollowsExtractor::postVisitStmtList(const StmtListNode& node) {
    nestingBlocksStack.pop(); // remove nesting block
}

void FollowsExtractor::processCurrStmt(const StmtNode& node) {
    // ai-gen start(gpt-4, 2)
    /*
    prompt:
    Given an AST and this definition for Follows/Follows*:
    For any statements s1 and s2, where s1 and s2 are line numbers: Follows(s1, s2) holds if they are at the same nesting level, in the same statement list (stmtLst), and s2 appears in the program text immediately after s1.
    Follows*(s1, s2) holds if Follows(s1, s2) or Follows(s1, s) and Follows*(s, s2) for some statement s.
    Suppose I have a DesignExtractor class that contains the AST root node. How do you extract Follows* relationship from the AST using visitor pattern?
    Follow-up: If the program has multiple statement blocks, e.g. while x { x = x + 1; y = y + 1; if x > 0 { x = 2; y = 2;}}, how does currStmtStack handle extract Follows* in that case
     */
    int currLine = node.getLineNum();
    // Update the Follows* relationships for prev lines in this block
    for (const int& prevLine : nestingBlocksStack.top()) {
        addFollows(prevLine, currLine);
    }
    nestingBlocksStack.top().push_back(currLine);
    // ai-gen end
}

void FollowsExtractor::addFollows(int prevLine, int currLine) {
    pkbWriter->setFollowsRelationship(prevLine, currLine);
}
