#include "ParentExtractor.h"

ParentExtractor::ParentExtractor(PKBWriter& pkbWriter) : Extractor(pkbWriter) {}

void ParentExtractor::visitIf(const IfNode& node) {
  parents.push_back(node.getLineNum());
}

void ParentExtractor::visitWhile(const WhileNode& node) {
  parents.push_back(node.getLineNum());
}

void ParentExtractor::postVisitIf(const IfNode& node) { parents.pop_back(); }

void ParentExtractor::postVisitWhile(const WhileNode& node) {
  parents.pop_back();
}

void ParentExtractor::visitStmtList(const StmtListNode& node) {
  if (parents.empty()) return;

  std::vector<int> childrenLineNums = node.getChildrenLineNums();
  int immediateParent = parents.back();
  for (int childLine : childrenLineNums) {
    addParent(immediateParent, childLine);
    for (int p : parents) {
      addParentStar(p, childLine);
    }
  }
}

void ParentExtractor::addParent(int parent, int child) {
  pkbWriter.setParentRelationship(parent, child);
}

void ParentExtractor::addParentStar(int parent, int child) {
  pkbWriter.setParentStarRelationship(parent, child);
}
