#include "StatementStorage.h"
#include "../../pkb/ConstantValues.h" 

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

// Constructor
StatementStorage::StatementStorage() {}

// Setter for each statement type
void StatementStorage::setReadStatement(int statementNumber) {
    allStmtStorage[READ].insert(statementNumber);
}

void StatementStorage::setPrintStatement(int statementNumber) {
    allStmtStorage[PRINT].insert(statementNumber);
}

void StatementStorage::setAssignStatement(int statementNumber) {
    allStmtStorage[ASSIGN].insert(statementNumber);
}

void StatementStorage::setCallStatement(int statementNumber) {
    allStmtStorage[CALL].insert(statementNumber);
}

void StatementStorage::setIfStatement(int statementNumber) {
    allStmtStorage[IF].insert(statementNumber);
}

void StatementStorage::setWhileStatement(int statementNumber) {
    allStmtStorage[WHILE].insert(statementNumber);
}

std::unordered_set<int> StatementStorage::getAllStatements() {
    std::unordered_set<int> allStatements;

    for (const auto& entry : allStmtStorage) {
        const std::unordered_set<int>& statementNumbers = entry.second;
        allStatements.insert(statementNumbers.begin(), statementNumbers.end());
    }
    return allStatements;
}

// Getter for each statement type
std::unordered_set<int> StatementStorage::getAllReadStatements() {
    return allStmtStorage[READ];
}

std::unordered_set<int> StatementStorage::getAllPrintStatements() {
    return allStmtStorage[PRINT];
}

std::unordered_set<int> StatementStorage::getAllAssignStatements() {
    return allStmtStorage[ASSIGN];
}

std::unordered_set<int> StatementStorage::getAllCallStatements() {
    return allStmtStorage[CALL];
}

std::unordered_set<int> StatementStorage::getAllIfStatements() {
    return allStmtStorage[IF];
}

std::unordered_set<int> StatementStorage::getAllWhileStatements() {
    return allStmtStorage[WHILE];
}

std::unordered_set<int> StatementStorage::getStatementNumbersFromStatementType(std::string statementType) {
    return allStmtStorage[statementType];
}

std::string StatementStorage::getStatementTypeFromStatementNumber(int statementNumber) {
    for (const auto& entry : allStmtStorage) {
        const std::unordered_set<int>& statementNumbers = entry.second;
        if (statementNumbers.count(statementNumber)) {
            return entry.first;
        }
    }

    return "";  // Return empty string if statement number is not found
}