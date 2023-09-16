#include "PatternExtractor.h"


PatternExtractor::PatternExtractor(PKBWriter *pkbWriter) : Extractor(pkbWriter) {}

std::string PatternExtractor::nodeToPostfixString(TNode* node) {
    if (!node) return "";
    if (node->getType() == TNodeType::TNODE_CONST || node->getType() == TNodeType::TNODE_VAR) {
        return node->getValue();
    }

    assert(node->getChildren().size() == 2);
    std::string left = nodeToPostfixString(node->getChildren()[0]);
    std::string right = nodeToPostfixString(node->getChildren()[1]);
    return left + right + node->getValue();
}

void PatternExtractor::visitAssign(const AssignNode *node) {
    std::string varName = node->getChildren()[0]->getValue();
    std::string postfixExpr = nodeToPostfixString(node->getChildren()[1]);
    pkbWriter->setAssignPattern(node->getLineNum(), varName, postfixExpr);
}



