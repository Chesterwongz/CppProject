#include "StatementStorage.h"
#include "../../pkb/ConstantValues.h" 

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

// Constructor
StatementStorage::StatementStorage() {}

// Setter for each statement type
void StatementStorage::setStatement(int statementNumber, std::string statementType) {
    allStmtStorage[statementType].insert(statementNumber);
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
std::unordered_set<int> StatementStorage::getStatement(std::string statementType) {
    return allStmtStorage[statementType];
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