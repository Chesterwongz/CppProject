#include "UsesExtractor.h"

UsesExtractor::UsesExtractor() : Extractor() {}
UsesExtractor::UsesExtractor(PkbWriter *pkbWriter) : Extractor(pkbWriter) {}

void UsesExtractor::visitProcedure(const ProcNode *node) {
    procName = node->getValue();
}

void UsesExtractor::visitAssign(const AssignNode *node) {
    stmtStates.push_back({node->getLineNum(), {}, true});
}

void UsesExtractor::visitIf(const IfNode *node) {
    stmtStates.push_back({node->getLineNum()});
}

void UsesExtractor::visitWhile(const WhileNode *node) {
    stmtStates.push_back({node->getLineNum()});
}

void UsesExtractor::visitPrint(const PrintNode *node) {
    stmtStates.push_back({node->getLineNum()});
}

void UsesExtractor::visitVariable(const VarNode *node) {
    if (stmtStates.empty()) {
        // no valid stmts visited before this variable node
        return;
    }
    StmtState& currState = stmtStates.back();
    if (currState.isAnticipateAssignLhs) {
        // LHS of assign statement, do not add to uses
        currState.isAnticipateAssignLhs = false;
        return;
    }
    currState.varsUsed.insert(node->getValue());
}

void UsesExtractor::processCurrState() {
    StmtState& currState = stmtStates.back();
    for (const std::string& var : currState.varsUsed) {
        for (const StmtState& state : stmtStates) {
            usesMap[var].insert(state.lineNum);
        }
    }
}

void UsesExtractor::postVisit() {
    processCurrState();
    stmtStates.pop_back();
}

void UsesExtractor::postVisitAssign(const AssignNode *node) {
    postVisit();
}

void UsesExtractor::postVisitIf(const IfNode *node) {
    postVisit();
}

void UsesExtractor::postVisitWhile(const WhileNode *node) {
    postVisit();
}

void UsesExtractor::postVisitPrint(const PrintNode *node) {
    postVisit();
}

std::map<std::string, std::set<int>> UsesExtractor::getUsesMap() {
    return usesMap;
}

