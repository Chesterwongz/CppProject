#include "PatternExtractor.h"


PatternExtractor::PatternExtractor(PKBWriter& pkbWriter) : Extractor(pkbWriter) {}

std::string PatternExtractor::nodeToPostfixString(const TNode& node) {
    if (node.getType() == TNodeType::TNODE_CONST || node.getType() == TNodeType::TNODE_VAR) {
        return node.getValue();
    }

    assert(node.getChildren().size() == 2);
    std::string left = nodeToPostfixString(node.getChildAt(0));
    std::string right = nodeToPostfixString(node.getChildAt(1));
    return left + " " + right + " " + node.getValue();
}

void PatternExtractor::getControlVars(std::unordered_set<std::string>& vars, const TNode& node) {
    if (node.getType() == TNodeType::TNODE_VAR) {
        vars.insert(node.getValue());
    }
    for (const auto child : node.getChildren()) {
        getControlVars(vars, *child);
    }
}

void PatternExtractor::visitAssign(const AssignNode& node) {
    std::string varName = node.getChildValueAt(0);
    std::string postfixExpr = " " + nodeToPostfixString(node.getChildAt(1)) + " ";
    pkbWriter.setAssignPattern(varName, postfixExpr, node.getLineNum());
}

void PatternExtractor::visitWhile(const WhileNode& node) {
    processContainerStmt(StmtType::WHILE, node);
}

void PatternExtractor::visitIf(const IfNode& node) {
    processContainerStmt(StmtType::IF, node);
}

void PatternExtractor::processContainerStmt(StmtType stmtType, const StmtNode& node) {
    std::unordered_set<std::string> controlVars;
    getControlVars(controlVars, node.getChildAt(0));
    for (auto& var : controlVars) {
        if (stmtType == StmtType::WHILE) {
            pkbWriter.setWhilePattern(node.getLineNum(), var);
        } else {
            pkbWriter.setIfPattern(node.getLineNum(), var);
        }
    }
}

