#include "ParentExtractor.h"

ParentExtractor::ParentExtractor(PKBWriter *pkbWriter) : Extractor(pkbWriter) {}

void ParentExtractor::visitIf(const IfNode *node) {
    parents.push_back(node->getLineNum());
}

void ParentExtractor::visitWhile(const WhileNode *node) {
    parents.push_back(node->getLineNum());
}

void ParentExtractor::postVisitIf(const IfNode *node) {
    parents.pop_back();
}

void ParentExtractor::postVisitWhile(const WhileNode *node) {
    parents.pop_back();
}

void ParentExtractor::visitStmtList(const StmtListNode *node) {
    std::vector<int> childrenLineNums = node->getChildrenLineNums();
    for (int childLine : childrenLineNums) {
        for (int parent : parents) {
            addParent(parent, childLine);
        }
    }
}

void ParentExtractor::addParent(int parent, int child) {
    pkbWriter->setParentRelationship(parent, child);
}
