#include "ModifiesExtractor.h"

ModifiesExtractor::ModifiesExtractor() = default;
ModifiesExtractor::ModifiesExtractor(PkbWriter *pkbWriter) : Extractor(pkbWriter) {}

void ModifiesExtractor::visitProcedure(const ProcNode *node) {
    procName = node->getValue();
}

void ModifiesExtractor::visitAssign(const AssignNode *node) {
    stmtStates.push_back({node->getLineNum(), {}, true});
}

void ModifiesExtractor::visitIf(const IfNode *node) {
    stmtStates.push_back({node->getLineNum(), {}, false});
}

void ModifiesExtractor::visitWhile(const WhileNode *node) {
    stmtStates.push_back({node->getLineNum(), {}, false});
}

void ModifiesExtractor::visitRead(const ReadNode *node) {
    stmtStates.push_back({node->getLineNum(), {}, true});
}

void ModifiesExtractor::visitVariable(const VarNode *node) {
    if (stmtStates.empty() || !stmtStates.back().isAnticipateVar) {
        // no valid stmt before this var, or, prev stmt/container is not going to modify this var
        return;
    }

    ModifiesStmtState &currState = stmtStates.back();
    currState.varsModified.insert(node->getValue());
    currState.isAnticipateVar = false;
}

void ModifiesExtractor::processCurrState() {
    ModifiesStmtState &currState = stmtStates.back();
    for (const std::string &var : currState.varsModified) {
        addModifies(currState.lineNum, var);
    }
}

void ModifiesExtractor::postVisit() {
    processCurrState();
    stmtStates.pop_back();
}

void ModifiesExtractor::postVisitAssign(const AssignNode *node) {
    postVisit();
}

void ModifiesExtractor::postVisitIf(const IfNode *node) {
    postVisit();
}

void ModifiesExtractor::postVisitWhile(const WhileNode *node) {
    postVisit();
}

void ModifiesExtractor::postVisitRead(const ReadNode *node) {
    postVisit();
}

std::map<std::string, std::set<int>> ModifiesExtractor::getModifiedMap() {
    return modifiesMap;
}

void ModifiesExtractor::addModifies(int lineNum, const std::string &var) {
    modifiesMap[var].insert(lineNum);
}

