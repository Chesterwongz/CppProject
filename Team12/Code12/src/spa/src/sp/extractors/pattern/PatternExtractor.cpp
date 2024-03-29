#include "PatternExtractor.h"

PatternExtractor::PatternExtractor(PKBWriter& pkbWriter)
    : Extractor(pkbWriter) {}

std::string PatternExtractor::nodeToPostfixString(const TNode& node) {
  if (node.getType() == TNodeType::TNODE_CONST ||
      node.getType() == TNodeType::TNODE_VAR) {
    return node.getValue();
  }

  assert(node.getChildren().size() == 2);
  std::string left = nodeToPostfixString(node.getChildAt(common::LEFT_CHILD));
  std::string right = nodeToPostfixString(node.getChildAt(common::RIGHT_CHILD));
  return left + " " + right + " " + node.getValue();
}

void PatternExtractor::getControlVars(std::unordered_set<std::string>& vars,
                                      const TNode& node) {
  if (node.getType() == TNodeType::TNODE_VAR) {
    vars.insert(node.getValue());
  }
  for (const auto child : node.getChildren()) {
    getControlVars(vars, *child);
  }
}

void PatternExtractor::visitAssign(const AssignNode& node) {
  std::string varName = node.getChildValueAt(common::LEFT_CHILD);
  std::string postfixExpr =
      " " + nodeToPostfixString(node.getChildAt(common::RIGHT_CHILD)) + " ";
  pkbWriter.addAssignPattern(varName, postfixExpr, node.getLineNum());
}

void PatternExtractor::visitWhile(const WhileNode& node) {
  processContainerStmt(StmtType::WHILE, node);
}

void PatternExtractor::visitIf(const IfNode& node) {
  processContainerStmt(StmtType::IF, node);
}

void PatternExtractor::processContainerStmt(StmtType stmtType,
                                            const StmtNode& node) {
  std::unordered_set<std::string> controlVars;
  getControlVars(controlVars, node.getChildAt(common::FIRST_CHILD));
  for (auto& var : controlVars) {
    if (stmtType == StmtType::WHILE) {
      pkbWriter.addWhilePattern(node.getLineNum(), var);
    } else {
      pkbWriter.addIfPattern(node.getLineNum(), var);
    }
  }
}
