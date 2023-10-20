#include "ParentExtractor.h"

ParentExtractor::ParentExtractor(PKBWriter& pkbWriter) : Extractor(pkbWriter) {}

void ParentExtractor::visitIf(const IfNode& node) {
  parents.push(node.getLineNum());
}

void ParentExtractor::visitWhile(const WhileNode& node) {
  parents.push(node.getLineNum());
}

void ParentExtractor::postVisitIf(const IfNode& node) { parents.pop(); }

void ParentExtractor::postVisitWhile(const WhileNode& node) { parents.pop(); }

void ParentExtractor::visitStmtList(const StmtListNode& node) {
  if (parents.empty()) return;

  std::vector<int> childrenLineNums = node.getChildrenLineNums();
  int immediateParent = parents.top();
  for (int childLine : childrenLineNums) {
    pkbWriter.addParent(immediateParent, childLine);
  }
}
