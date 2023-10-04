#include "UsesExtractor.h"

UsesExtractor::UsesExtractor(PKBWriter& pkbWriter) : Extractor(pkbWriter) {}

void UsesExtractor::visitProcedure(const ProcNode& node) {
  procName = node.getValue();
}

void UsesExtractor::visitAssign(const AssignNode& node) {
  stmtStates.push_back({TNodeType::TNODE_ASSIGN, node.getLineNum(), true});
}

void UsesExtractor::visitIf(const IfNode& node) {
  stmtStates.push_back({TNodeType::TNODE_IF, node.getLineNum()});
}

void UsesExtractor::visitWhile(const WhileNode& node) {
  stmtStates.push_back({TNodeType::TNODE_WHILE, node.getLineNum()});
}

void UsesExtractor::visitPrint(const PrintNode& node) {
  stmtStates.push_back({TNodeType::TNODE_PRINT, node.getLineNum()});
}

void UsesExtractor::visitRead(const ReadNode& node) {
  stmtStates.push_back({TNodeType::TNODE_READ, node.getLineNum(), true});
}

void UsesExtractor::visitVariable(const VarNode& node) {
  if (stmtStates.empty()) {
    // no valid stmts visited before this variable node
    return;
  }
  UsesStmtState& currState = stmtStates.back();
  if (currState.shouldIgnoreVar) {
    if (currState.nodeType == TNodeType::TNODE_ASSIGN) {
      // LHS of assign statement, do not add to uses
      currState.shouldIgnoreVar = false;
    }
    // ignore this variable
    return;
  }
  currState.varsUsed.insert(node.getValue());
}

void UsesExtractor::processCurrState() {
  UsesStmtState& currState = stmtStates.back();
  for (const std::string& var : currState.varsUsed) {
    for (const UsesStmtState& state : stmtStates) {
      addUses(state.lineNum, var);
    }
  }
}

void UsesExtractor::postVisit() {
  processCurrState();
  stmtStates.pop_back();
}

void UsesExtractor::postVisitAssign(const AssignNode& node) { postVisit(); }

void UsesExtractor::postVisitIf(const IfNode& node) { postVisit(); }

void UsesExtractor::postVisitWhile(const WhileNode& node) { postVisit(); }

void UsesExtractor::postVisitPrint(const PrintNode& node) { postVisit(); }

void UsesExtractor::postVisitRead(const ReadNode& node) {
  stmtStates.pop_back();
}

void UsesExtractor::addUses(int lineNum, const std::string& var) {
  pkbWriter.setUsesRelationship(var, lineNum);
  pkbWriter.setUsesRelationship(var, procName);
}
