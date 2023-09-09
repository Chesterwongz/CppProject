#include "EntityExtractor.h"

EntityExtractor::EntityExtractor() = default;

EntityExtractor::EntityExtractor(PkbWriter *pkbWriter) : Extractor(pkbWriter) {}

void EntityExtractor::visitAssign(const AssignNode *node) {
    assignStmts.insert(node->getLineNum());
}

void EntityExtractor::visitCall(const CallNode *node) {
    callStmts.insert(node->getLineNum());
}

void EntityExtractor::visitIf(const IfNode *node) {
    ifStmts.insert(node->getLineNum());
}

void EntityExtractor::visitPrint(const PrintNode *node) {
    printStmts.insert(node->getLineNum());
}

void EntityExtractor::visitRead(const ReadNode *node) {
    readStmts.insert(node->getLineNum());
}

void EntityExtractor::visitWhile(const WhileNode *node) {
    whileStmts.insert(node->getLineNum());
}

void EntityExtractor::visitVariable(const VarNode *node) {
    variables.insert(node->getValue());
}

void EntityExtractor::visitConstant(const ConstNode *node) {
    constants.insert(node->getValue());
}

void EntityExtractor::visitProcedure(const ProcNode *node) {
    procedures.insert(node->getValue());
}

std::unordered_set<std::string> EntityExtractor::getVariables() {
    return variables;
}

std::unordered_set<std::string> EntityExtractor::getConstants() {
    return constants;
}

std::unordered_set<std::string> EntityExtractor::getProcedures() {
    return procedures;
}

std::unordered_set<int> EntityExtractor::getAssignStmts() {
    return assignStmts;
}

std::unordered_set<int> EntityExtractor::getCallStmts() {
    return callStmts;
}

std::unordered_set<int> EntityExtractor::getIfStmts() {
    return ifStmts;
}

std::unordered_set<int> EntityExtractor::getPrintStmts() {
    return printStmts;
}

std::unordered_set<int> EntityExtractor::getReadStmts() {
    return readStmts;
}

std::unordered_set<int> EntityExtractor::getWhileStmts() {
    return whileStmts;
}

