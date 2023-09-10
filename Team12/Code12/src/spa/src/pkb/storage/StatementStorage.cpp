# include "StatementStorage.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

// Constructor
StatementStorage::StatementStorage() {}

// Setter for each statement type
void StatementStorage::setReadStatement(int statementNumber) {
    readStmtStorage.insert(statementNumber);
}

void StatementStorage::setPrintStatement(int statementNumber) {
    printStmtStorage.insert(statementNumber);
}

void StatementStorage::setAssignStatement(int statementNumber) {
    assignStmtStorage.insert(statementNumber);
}

void StatementStorage::setCallStatement(int statementNumber) {
    callStmtStorage.insert(statementNumber);
}

void StatementStorage::setIfStatement(int statementNumber) {
    ifStmtStorage.insert(statementNumber);
}

void StatementStorage::setWhileStatement(int statementNumber) {
    whileStmtStorage.insert(statementNumber);
}

// Getter for each statement type
std::unordered_set<int>& StatementStorage::getAllReadStatements() {
    return readStmtStorage;
}

std::unordered_set<int>& StatementStorage::getAllPrintStatements() {
    return printStmtStorage;
}

std::unordered_set<int>& StatementStorage::getAllAssignStatements() {
    return assignStmtStorage;
}

std::unordered_set<int>& StatementStorage::getAllCallStatements() {
    return callStmtStorage;
}

std::unordered_set<int>& StatementStorage::getAllIfStatements() {
    return ifStmtStorage;
}

std::unordered_set<int>& StatementStorage::getAllWhileStatements() {
    return whileStmtStorage;
}

